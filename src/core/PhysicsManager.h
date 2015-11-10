#ifndef __PHYSICS_MANAGER_H
#define __PHYSICS_MANAGER_H

#include "GlobalIncludes.h"

enum collisionTypes
{
    COLLIDE_NOTHING = 0,
    COLLIDE_GROUND  = 1,
    COLLIDE_OBJECT  = 2
};

class PhysicsManager
{
    public:
        PhysicsManager();
        ~PhysicsManager();

        void AddRigidBody(btCollisionShape* collisionShape,
                          btVector3 origin     = btVector3(0,0,0),
                          btScalar mass        = btScalar(0),
                          btScalar restitution = btScalar(1.0f),
                          btVector3 inertia    = btVector3(0.0f, 0.0f, 0.0f),
                          bool kinematic       = false);

        glm::mat4 GetModelMatrixAtIndex(int index);
        int GetNumObjects();

        void Update();

        void ApplyForceAtIndex(btVector3 force, int index);

    private:

        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher *dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;

};

#endif
