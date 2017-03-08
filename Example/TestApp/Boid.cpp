#include "Boid.h"
#include <math.h>
#include "Matrix4D.h"

//////////////////////////////
// STEERING BEHAVIORS ///////
/////////////////////////////

//Sugue un punto fijo
Vector3D CBoid::Seek(const Vector3D& vTargetPosition)
{
	Vector3D vDirection = Normalize(vTargetPosition - m_vPosition);
	return vDirection * SEEK_FORCE;
}

//Corre de un punto fijo
Vector3D CBoid::Flee(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = m_vPosition - vTargetPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius)
		return Vector3D(0,0,0);
	return vDirection * FLEE_FORCE;
}

//Llega a un punto y se detiene
Vector3D CBoid::Arrive(const Vector3D& vTargetPosition, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0,0,0);
	Vector3D vDirection = Normalize(vDistance);
	if (Magnitude(vDistance) > fRadius) {
		return vDirection * ARRIVE_FORCE;
	}
	return (vDirection * ARRIVE_FORCE) * (Magnitude(vDistance)/fRadius) ;
}

//Persigue a un objetivo en movimiento
Vector3D CBoid::Pursue(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnitude(vPredictionPos - vTargetPosition);
	if (Magnitude(vDistance) < fPredictionRadius )
	{
		fMaxTimePrediction = Magnitude(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	return Normalize(vPredictionPos - m_vPosition) * PURSUE_FORCE;
}
//Corre de un objetivo en movimiento
Vector3D CBoid::Evade(const Vector3D & vTargetPosition, const Vector3D & vTargetVelocity, float fMaxTimePrediction, float fRadius)
{
	Vector3D vDistance = vTargetPosition - m_vPosition;
	if (Magnitude(vDistance) < 0) 
		return Vector3D(0, 0, 0);
	if (Magnitude(vDistance) > fRadius)
		return Vector3D(0,0,0);
	Vector3D vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	float fPredictionRadius = Magnitude(vPredictionPos - vTargetPosition);
	if (Magnitude(vDistance) < fPredictionRadius)
	{

		fMaxTimePrediction = Magnitude(vDistance) / fPredictionRadius;
		vPredictionPos = vTargetPosition + vTargetVelocity * fMaxTimePrediction;
	}
	else 
	{
		vDistance = vPredictionPos - m_vPosition;
	}
	return Normalize(m_vPosition - vPredictionPos) * EVADE_FORCE;
}
//vaga por el mundo
Vector3D CBoid::Wander(const Vector3D & vWorldSize, float fRadius, float fMaxTime,float fDelta)
{

	m_fWanderTime += fDelta;
	if (m_bWanderArrived) {
		m_vWanderSeekPoint = Vector3D(vWorldSize.x * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX ) - vWorldSize.x/2.f),
			vWorldSize.y * static_cast <float> (rand()) / (static_cast <float> (RAND_MAX) - vWorldSize.y/2.f), 0);
		m_bWanderArrived = false;
	}
	if (Magnitude(m_vWanderSeekPoint - m_vPosition) < fRadius) {
		m_bWanderArrived = true;
		return Vector3D(0, 0, 0);
	}
	if (m_fWanderTime > fMaxTime) {
		m_bWanderArrived = true;
		m_fWanderTime = 0;
	}
	return Normalize(m_vWanderSeekPoint - m_vPosition) * WANDER_FORCE;
}
//Vaga por el mundo, es m�s estable que wander 1
Vector3D CBoid::Wander2(const float fOffset, float fRadius, float fVisionRange)
{
	Vector3D vForce;
	Vector3D vPoint;

	Vector3D vProyectedPoint = m_vPosition + Vector3D(1, 0, 0) * fOffset;
	float fBoidAngle = 0;
	vProyectedPoint = m_vPosition + (m_vDirection * fOffset);
	fBoidAngle = atan2(m_vDirection.y, m_vDirection.x);
	float fRandAngle = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (fVisionRange))) - fVisionRange / 2;
	vPoint = vProyectedPoint + Vector3D(cos(fBoidAngle + fRandAngle), sin(fBoidAngle + fRandAngle), 0);
	vForce = Normalize(vPoint - m_vPosition) * WANDER_FORCE;
	
	if (Magnitude(vPoint - m_vPosition) < fRadius) {
		return Vector3D(0, 0, 0);
	}

	return vForce;
}
//Evade un obstaculo
Vector3D CBoid::ObstacleAvoidance(float fProyDist)
{
	Vector3D vMedProyection = m_vPosition + fProyDist *0.5f * Normalize(m_vDirection);
	vMedProyection = vMedProyection* m_fVelocity;
	Vector3D vFinProyection = vMedProyection * 2.f;
	//m_line.vertices[1].x = Magnitude(vFinProyection - m_vPosition) +0.05f;
	Vector3D shortestCollisionDir;
	const float NULL_DISTANCE = 30000;
	float shortestCollisionDis = NULL_DISTANCE;
	for (auto &item : *m_pObstacleList) {
		if (Magnitude(item->GetPosition() - m_vPosition) < (m_fRadius + item->GetRadius())) {
			//Colisi�n con boid
			if (Magnitude(item->GetPosition() - m_vPosition) < shortestCollisionDis)
			{
				shortestCollisionDis = Magnitude(item->GetPosition() - m_vPosition);
				shortestCollisionDir = Normalize(m_vPosition - item->GetPosition());
			}
		}
		if (Magnitude(item->GetPosition() - vMedProyection) < (m_fRadius + item->GetRadius())) {
			//Colisi�n con Medio
			if (Magnitude(item->GetPosition() - m_vPosition) < shortestCollisionDis)
			{
				shortestCollisionDis = Magnitude(item->GetPosition() - vMedProyection);
				shortestCollisionDir = Normalize(vMedProyection - item->GetPosition());
			}
		}
		if (Magnitude(item->GetPosition() - vFinProyection) < (m_fRadius + item->GetRadius())) {
			//Colisi�n con Final
			if (Magnitude(item->GetPosition() - m_vPosition) < shortestCollisionDis)
			{
				shortestCollisionDis = Magnitude(item->GetPosition() - vFinProyection);
				shortestCollisionDir = Normalize(vFinProyection - item->GetPosition());
			}
		}
	}
	if (shortestCollisionDis != NULL_DISTANCE)
		return shortestCollisionDir * BIG_FORCE;
	return Vector3D(0, 0, 0);
}
//Evade un obstaculo sin dejar huecos
Vector3D CBoid::ObstacleAvoidance2()
{
	const float POFFSET0 = 0.05f;
	const float POFFSET1 = 0.05f;
	Vector3D PerpendicularDir(-m_vDirection.y,m_vDirection.x,m_vDirection.z);
	Vector3D topLeftPoint = m_vPosition + POFFSET0 * PerpendicularDir;
	Vector3D topRightPoint = topLeftPoint + m_vDirection * POFFSET1;
	Vector3D botLeftPoint = m_vPosition - POFFSET0 * PerpendicularDir;
	Vector3D botRightPint = botLeftPoint + m_vDirection * POFFSET1;

	Vector3D topVector = topRightPoint - topLeftPoint;
	Vector3D rightVector = botRightPint - topRightPoint;
	Vector3D botVector = botLeftPoint - botRightPint;
	Vector3D leftVector = botLeftPoint - topLeftPoint;

	//m_line.vertices[1].x = Magnitude(topRightPoint - m_vPosition) + 0.05f;//
	for (auto &it : *m_pObstacleList)
	{
		Vector3D distancePoint = (Dot((it->GetPosition()  - topLeftPoint),(topVector)) / Magnitude(topVector)) * m_vDirection;
		if (Magnitude(distancePoint) < 0)
			distancePoint = topLeftPoint;
		if (Magnitude(distancePoint) > Magnitude(topVector))
			distancePoint = topRightPoint;
		if (Magnitude(it->GetPosition() - distancePoint) < it->GetRadius()) 
		{
			//Colisi�n
			return Normalize(distancePoint - it->GetPosition()) * BIG_FORCE;
		}

		distancePoint = (Dot((it->GetPosition() - botLeftPoint), (botVector)) / Magnitude(botVector)) * m_vDirection;
		if (Magnitude(distancePoint) < 0)
			distancePoint = topLeftPoint;
		if (Magnitude(distancePoint) > Magnitude(topVector))
			distancePoint = topRightPoint;
		if (Magnitude(it->GetPosition() - distancePoint) < it->GetRadius())
		{
			//Colisi�n
			return Normalize(distancePoint - it->GetPosition()) * BIG_FORCE;
		}

		distancePoint = (Dot((it->GetPosition() - topRightPoint), (rightVector)) / Magnitude(rightVector)) * m_vDirection;
		if (Magnitude(distancePoint) < 0)
			distancePoint = topRightPoint;
		if (Magnitude(distancePoint) > Magnitude(rightVector))
			distancePoint = botRightPint;
		if (Magnitude(it->GetPosition() - distancePoint) < it->GetRadius())
		{
			//Colisi�n
			return Normalize(distancePoint - it->GetPosition()) * BIG_FORCE;
		}

		distancePoint = (Dot((it->GetPosition() - botLeftPoint), (leftVector)) / Magnitude(leftVector)) * m_vDirection;
		if (Magnitude(distancePoint) < 0)
			distancePoint = botLeftPoint;
		if (Magnitude(distancePoint) > Magnitude(topVector))
			distancePoint = topLeftPoint;
		if (Magnitude(it->GetPosition() - distancePoint) < it->GetRadius())
		{
			//Colisi�n
			return Normalize(distancePoint - it->GetPosition()) * BIG_FORCE;
		}
	}


	

	return Vector3D(0,0,0);
}
Vector3D CBoid::CircleMovement(float fRadius, float delta)
{
	m_fCircleParam += CIRCLE_PARAM_VEL * delta;
	Vector3D seekPoint =  Vector3D(cosf(m_fCircleParam), sinf(m_fCircleParam), 0) * fRadius; //Genera un punto de seek a partir del seno y coseno de un parametro que incrementa con el tiempo
	return Seek(seekPoint); //Regresa seek a ese punto
}
//=========== Sigue una serie de puntos establecidos en m_followPathVector =================
Vector3D CBoid::FollowPath()
{
	if (m_bFirstFollow) {
		m_iActualPoint = 0;
		m_bFirstFollow = false;
	}
	Vector3D force(0, 0, 0);

	if (m_iActualPoint < m_followPathVector.size())
	{
		force = Seek(m_followPathVector[m_iActualPoint]);
		Vector3D linePoint;
		if (m_iActualPoint < m_followPathVector.size()-1)
			linePoint = m_followPathVector[m_iActualPoint + 1] - m_followPathVector[m_iActualPoint];
		else
			linePoint = m_followPathVector[m_iActualPoint] - m_followPathVector[m_iActualPoint-1];
		Vector3D distancePoint = (Dot((m_followPathVector[m_iActualPoint] - m_vPosition), linePoint) / Magnitude(linePoint)) * Normalize(linePoint) ;
		force += (distancePoint - m_vPosition) * FOLLOW_PATH_LINE_FORCE;
		if (Magnitude(m_followPathVector[m_iActualPoint] - m_vPosition) < FOLLOW_POINT_RADIUS) {
			m_iActualPoint++;
		}
	}

	return force;
}

Vector3D CBoid::FollowPathLoop()
{
	if (m_bFirstFollow) {
		m_iActualPoint = 0;
		m_bFirstFollow = false;
	}
	Vector3D force(0, 0, 0);

	if (m_iActualPoint < m_followPathVector.size())
	{
		force = Seek(m_followPathVector[m_iActualPoint]);
		Vector3D linePoint;
		if (m_iActualPoint < m_followPathVector.size() - 1)
			linePoint = m_followPathVector[m_iActualPoint + 1] - m_followPathVector[m_iActualPoint];
		else
			linePoint = m_followPathVector[m_iActualPoint] - m_followPathVector[m_iActualPoint - 1];
		Vector3D distancePoint = (Dot((m_followPathVector[m_iActualPoint] - m_vPosition), linePoint) / Magnitude(linePoint)) * Normalize(linePoint);
		force += (distancePoint - m_vPosition) * FOLLOW_PATH_LINE_FORCE;
		if (Magnitude(m_followPathVector[m_iActualPoint] - m_vPosition) < FOLLOW_POINT_RADIUS) {
			m_iActualPoint++;
		}
	}
	else
		m_bFirstFollow = true;

	return force;
}

Vector3D CBoid::FollowPathArrive()
{
	if (m_bFirstFollow) {
		m_iActualPoint = 0;
		m_bFirstFollow = false;
	}
	Vector3D force(0, 0, 0);

	if (m_iActualPoint < m_followPathVector.size())
	{
		force = Arrive(m_followPathVector[m_iActualPoint],ACTIVE_RADIUS);
		if (Magnitude(m_followPathVector[m_iActualPoint] - m_vPosition) < FOLLOW_POINT_RADIUS) {
			m_iActualPoint++;
		}
	}

	return force;
}

void CBoid::SetLider(bool islider)
{
	m_isLider = islider;
}

Vector3D CBoid::Flocking()
{
	Vector3D directions = m_vDirection;
	Vector3D forces(0,0,0);
	Vector3D center = m_vPosition;
	for (auto &it : *m_pWorldBoids)
	{
		Vector3D separation = it->GetPosition() - m_vPosition;
		float dist = Magnitude(separation);
		if (dist < FLOCKING_RADIUS)
		{
			center += (1 / 3.f)*(it->GetPosition() - m_vPosition);
		}
	}
	for (auto &it : *m_pWorldBoids)
	{
		Vector3D separation = it->GetPosition() - m_vPosition;
		float dist = Magnitude(separation);
		if (dist < FLOCKING_RADIUS && dist != 0)
		{
			directions += dynamic_cast<CBoid*>(it.get())->GetDirection();
			forces +=Normalize(separation) * (1 - FLOCKING_RADIUS / dist);
			forces +=  center - m_vPosition;
		}
	}
	forces += directions * SEEK_FORCE;
	return forces;
}

Vector3D CBoid::FollowTheLider()
{
	Vector3D forces(0, 0, 0);
	Vector3D center = m_vPosition;
	for (auto &it : *m_pWorldBoids)
	{
		Vector3D separation = it->GetPosition() - m_vPosition;
		float dist = Magnitude(separation);
		if (dist < FLOCKING_RADIUS && dist != 0)
		{
			center += (1 / 3.f)*(it->GetPosition() - m_vPosition);
		}
	}
	for (auto &it : *m_pWorldBoids)
	{
		Vector3D separation = it->GetPosition() - m_vPosition;
		float dist = Magnitude(separation);
		if (dist < FLOCKING_RADIUS && dist != 0)
		{
			forces += Normalize(separation) * (1 - FLOCKING_RADIUS / dist);
			forces += center - m_vPosition;

		}
		if (dist < FTL_RADIUS && dist != 0) {
			if (dynamic_cast<CBoid*>(it.get())->IsLider())
			{
				forces += Seek(it->GetPosition() - (dynamic_cast<CBoid*>(it.get())->GetDirection() * LIDER_SEPARATION));
			}
		}

	}
	return forces;
}

//============== Inicializar parametros ==============
void CBoid::Init()
{
	m_fCircleParam = 0.1f;
	m_vDirection = Vector3D(0, 0, 0);
	triangle.Create();
	//m_line.Create();
	m_isLider = false;
	m_bFirstFollow = true;
	m_iActualPoint = 0;

	m_followPathVector.push_back(Vector3D(0, 0, 0));
	m_followPathVector.push_back(Vector3D(0.5, 0.5, 0));
	m_followPathVector.push_back(Vector3D(-0.5, -0.5, 0));
}

void CBoid::Destroy()
{
	triangle.Destroy();
}

void CBoid::Update(float delta)
{
	Vector3D forces(0,0,0);
	for (auto &item : m_Targets) 
	{
		switch (item.second)
		{
		case SteeringBehavior::E::kEvade:
			forces += Evade(item.first->GetPosition(), 
				(std::dynamic_pointer_cast<CBoid>(item.first))->GetDirection() * (dynamic_cast<CBoid*>(item.first.get()))->GetVelocity(),MAX_TIME_PREDICTION,ACTIVE_RADIUS);
			break;
		case SteeringBehavior::E::kFlee:
			forces += Flee(item.first->GetPosition(), ACTIVE_RADIUS);
			break;
		case SteeringBehavior::E::kPursue:
			forces += Pursue(item.first->GetPosition(),
				(std::dynamic_pointer_cast<CBoid>(item.first))->GetDirection() * (dynamic_cast<CBoid*>(item.first.get()))->GetVelocity(), MAX_TIME_PREDICTION);
			break;
		case SteeringBehavior::E::kSeek:
			forces += Seek(item.first->GetPosition());
			break;
			case SteeringBehavior::E::kArrive :
				forces += Arrive(item.first->GetPosition(), ACTIVE_RADIUS);
			break;
		}
	}

	for (auto &item : m_States)
	{
		switch (item)
		{
		case SteeringStates::E::kWander :
			forces += Wander(Vector3D(2,2,0), 0.05f, 5.f, delta);
			break;
		case SteeringStates::E::kWander2:
			forces += Wander2(WANDER2_OFFSET,WANDER2_RADIUS,WANDER2_VISIONRANGE);
			break;
		case SteeringStates::E::kObstacleAvoidance:
			forces += ObstacleAvoidance(PROYECTION_DISTANCE);
			break;
		case SteeringStates::E::kObstacleAvoidance2:
			forces += ObstacleAvoidance2();
			break;
		case SteeringStates::E::kCircleMovement:
			forces += CircleMovement(CIRCLE_RADIUS, delta);
			break;
		case SteeringStates::E::kFollowPath:
			forces += FollowPath();
			break;
		case SteeringStates::E::kFollowPathLoop:
			forces += FollowPathLoop();
			break;
		case SteeringStates::E::kFollowPathArrive:
			forces += FollowPathArrive();
			break;
		case SteeringStates::E::kFlocking:
			forces += Flocking();
			break;
		case SteeringStates::E::kFollowTheLider:
			forces += FollowTheLider();
			break;
		}
	}
	Vector3D forces2(0,0,0);
	if (!(forces.x == 0 && forces.y == 0 && forces.z == 0)) {
		forces2 = Truncate(forces, MAX_ROTATION);
		m_vDirection += forces2;
		m_vDirection = Normalize(m_vDirection);
	}
	forces = Truncate(forces, MAX_SPEED);
	m_fVelocity = Magnitude(forces);
	m_vPosition += m_vDirection * m_fVelocity * delta;

	if (m_vPosition.x > 1) {
		m_vPosition.x = -1;
	}
	if (m_vPosition.x < -1) {
		m_vPosition.x = 1;
	}
	if (m_vPosition.y > 1) {
		m_vPosition.y = -1;
	}				
	if (m_vPosition.y < -1) {
		m_vPosition.y = 1;
	}

	Matrix4D transform = RotationZRH(atan2(-m_vDirection.y, m_vDirection.x));
	transform = transform * Translation(m_vPosition.x, m_vPosition.y, 0);
	triangle.Transform(transform.v);
	//m_line.Transform(transform.v);
}

void CBoid::Render()
{
	triangle.Draw();
	//m_line.Draw();
}

//A�adir objetivos que no se mueven
void CBoid::AddStaticTarget(Vector3D targetPos, SteeringBehavior::E behabior)
{
	std::shared_ptr<CBoid> target = std::make_shared<CBoid>();
	target->Init();
	target->SetPosition(targetPos);
	std::pair<std::shared_ptr<CGameObject>, SteeringBehavior::E> dataPair = { target, behabior };
	m_Targets.push_back(dataPair);
}
//A�adir objetivos que se mueven
void CBoid::AddDynamicTarget(std::shared_ptr <CGameObject> target, SteeringBehavior::E behavior)
{
	std::pair<std::shared_ptr<CGameObject>, SteeringBehavior::E> dataPair = { target, behavior };
	m_Targets.push_back(dataPair);
}
//A�adir estados de comportamiento
void CBoid::AddSteeringState(SteeringStates::E state)
{
	if (state == SteeringStates::E::kFollowPath)
		m_bFirstFollow = true;
	m_States.push_back(state);
}


//=========== GETS y SETS ===========

Vector3D CBoid::GetDirection()
{
	return m_vDirection;
}

void CBoid::SetObstacleList(std::vector<std::shared_ptr<CObstacle>>* pObstacleList)
{
	m_pObstacleList = pObstacleList;
}

void CBoid::SetFollowPathVector(std::vector<Vector3D> vector)
{
	m_followPathVector = vector;
}

void CBoid::SetWorldBoidsVector(std::vector<std::shared_ptr<CGameObject>>* worldBoids)
{
	m_pWorldBoids = worldBoids;
}

void CBoid::SetRadius(float radius)
{
	m_fRadius = radius;
}

float CBoid::GetRadius()
{
	return m_fRadius;
}
float CBoid::GetVelocity()
{
	return m_fVelocity;
}


CBoid::CBoid()
{
}


CBoid::~CBoid()
{
}

bool CBoid::IsLider()
{
	return m_isLider;
}
