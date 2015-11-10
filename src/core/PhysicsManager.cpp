#include "PhysicsManager.h"
#include "Game.h"

using namespace std;

PhysicsManager::PhysicsManager()
{
    // Initialize Bullet
    broadphase             = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher             = new btCollisionDispatcher(collisionConfiguration);
    solver                 = new btSequentialImpulseConstraintSolver();
    dynamicsWorld          = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

    // Add gravity
    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}

PhysicsManager::~PhysicsManager()
{
    // Free Bullet
    for(size_t i = 0; i < dynamicsWorld->getNumCollisionObjects(); i++)
    {
        dynamicsWorld->removeRigidBody( btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[i]) );
    }

    delete dynamicsWorld;
    delete broadphase;
    delete collisionConfiguration;
    delete dispatcher;
    delete solver;

    dynamicsWorld          = NULL;
    broadphase             = NULL;
    collisionConfiguration = NULL;
    dispatcher             = NULL;
    solver                 = NULL;

}

void PhysicsManager::AddRigidBody(btCollisionShape* collisionShape, btVector3 origin, btScalar mass, btScalar restitution, btVector3 inertia, bool kinematic)
{
    btDefaultMotionState* motionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), origin));
    if(mass > 0)
        collisionShape->calculateLocalInertia(mass, inertia);
    btRigidBody::btRigidBodyConstructionInfo constructionInfo(mass, motionState, collisionShape, inertia);
    btRigidBody* body = new btRigidBody(constructionInfo);
    body->setRestitution(restitution);
    body->setActivationState(DISABLE_DEACTIVATION);
    if(kinematic)
    {
        body->setCollisionFlags(body->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
        //body->setActivationState(DISABLE_DEACTIVATION);
    }
    dynamicsWorld->addRigidBody(body);
}

int PhysicsManager::GetNumObjects()
{
    return dynamicsWorld->getNumCollisionObjects();
}

glm::mat4 PhysicsManager::GetModelMatrixAtIndex(int index)
{
    if(index < 0 || index >= GetNumObjects())
    {
        cout << "ERROR! PhysicsManager::GetModelMatrixAtIndex tried to access: " << index << " which is not between 0 and " << GetNumObjects() << "." << endl;
        return glm::mat4(1.0f);
    }

    btTransform trans;
    btScalar m[16];
    btRigidBody* object = btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[index]);
    object->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);
    glm::mat4 modelMatrix = glm::make_mat4(m);
    return modelMatrix;
}

void PhysicsManager::Update()
{
    dynamicsWorld->stepSimulation(Game::GetInstance()->GetTimeDelta(), 1);
}

void PhysicsManager::ApplyForceAtIndex(btVector3 force, int index)
{
    if(index < 0 || index >= GetNumObjects())
    {
        cout << "ERROR! PhysicsManager::ApplyForceAtIndex tried to access: " << index << " which is not between 0 and " << GetNumObjects() << "." << endl;
        return;
    }

    btRigidBody* object = btRigidBody::upcast(dynamicsWorld->getCollisionObjectArray()[index]);
    object->applyCentralImpulse(force);
    object->clearForces();

}

