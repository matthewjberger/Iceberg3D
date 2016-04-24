#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "GlobalIncludes.h"
#include "Game.h"

namespace iceberg
{
    enum ICEBERGAPI collisionTypes
    {
        COLLIDE_NOTHING = 0,
        COLLIDE_GROUND = 1,
        COLLIDE_OBJECT = 2
    };

    class ICEBERGAPI PhysicsManager
    {
    public:
        PhysicsManager();
        ~PhysicsManager();

        void AddRigidBody(btCollisionShape* collisionShape,
            btVector3* origin = new btVector3(0, 0, 0),
            btScalar* mass = new btScalar(0),
            btScalar* restitution = new btScalar(1.0f),
            btVector3* inertia = new btVector3(0.0f, 0.0f, 0.0f),
            bool kinematic = false) const;

        glm::mat4 GetModelMatrixAtIndex(int index) const;
        int GetNumObjects() const;

        void Update(Game *game) const;

        void ApplyForceAtIndex(btVector3* force, int index) const;

    private:

        btBroadphaseInterface* broadphase;
        btDefaultCollisionConfiguration* collisionConfiguration;
        btCollisionDispatcher* dispatcher;
        btSequentialImpulseConstraintSolver* solver;
        btDiscreteDynamicsWorld* dynamicsWorld;
    };
}
#endif