#ifndef PARAMS_DREAMCATCHERS_H
#define PARAMS_DREAMCATCHERS_H

// ghost dreamcatcher parameters
namespace Ghost
{
    // slash attack parameters
    namespace Slash
    {
        float HEX_DURATION = 0.f; // the number of seconds before a hex goes away
        float HIT_FREQUENCY = 1.f; // number of times the hex hits the enemy per second
        float HEX_DAMAGE = 1.f; // damage dealt per hit
        /*
        * =0 : enemies cannot transmit the hex
        * >0 : enemies can transmit the hex repeatedly this degree of separation from the original hex
        *
        * example:
        * P = player
        * En = Enemy #n
        * ^n = this is the furthest-separated enemy to be hexed with transmissibility level n
        *
        *      "patient zero"
                       |
        *              V
        * P --hexed--> E0 --transmit--> E1 --transmit--> E2 --transmit--> E3
        *              ^0               ^1               ^2               ^3
        */
        int HEX_TRANSMISSIBILITY = 0; // how far from the originally hexed enemy (degree of separation) the hex can be transmitted
        int MAX_HEX_COUNT = 1; // the number of hexes the PLAYER can create with their slash attack (does not affect transmitted hexes)
        int MAX_HEXES_PER_ENEMY = 1; // the number of hexes an enemy can have on itself at a time
    }

    // dream attack parameters
    namespace Dream
    {
        bool RESTRICT_TO_8_DIRS = false; // whether or not the aiming should be restricted to 8 directons
        float MAX_AIMING_TIME = 1.f; // maximum time allowed for aiming. the attack will automatically fire in the chosen direction when time is up, if it is not cancelled
        float SPHERE_RADIUS = 10.f; // radius of fired projectile
        float SPHERE_DAMAGE = 5.f; // damage dealt by projectile
        float SPHERE_LIFETIME = 15.f; // the number of seconds before the projectile disappears
        float SPHERE_SPEED = 1.f; // how fast projectiles move
        int MAX_COEXISTING_SPHERES = 3; // the number of projectiles allowed to exist at once
        float ROTATION_SPEED = 10.f; // the max rotation speed of the projectile, in degrees per second
        /*
        * angle size:   small     medium            large
        *               \\V//    \\\\V////    \\\\\\\\V////////
        *                \V/      \\\V///       \\\\\\V//////
        * homing cone--> \V/       \\V//          \\\\V////
        *                 V         \V/             \\V//
        *                 V          V                V
        * projectile-->   O          O                O
        *
        * this example assumes the cone LENGTH does not change
        */
        float HOMING_CONE_ANGLE = 30.f; // the angle of the homing cone (how wide the cone is)
        /*
        * cone length:   small    medium      large
        *                                    \\\V///
        *                          \\V//      \\V//
        * homing cone-->   \V/      \V/        \V/
        *                   V        V          V
        * projectile-->     O        O          O
        *
        * this example assumes the cone ANGLE does not change
        */
        float HOMING_CONE_LENGTH = 10.f; // the length of the homing cone
        float DREAM_ENERGY_USAGE = 1.f; // ghost energy usage per projectile fired 
    }

    // jump parameters
    namespace Jump
    {
        /*
        * false = invincibility does not last the full jump time. invincibility will last for the number of seconds specified in INVINCIBILITY_TIME
        * true  = invincibility lasts the full jump time
        */
        bool FULL_JUMP_INVINCIBILITY = false; // whether or not jump invincibility lasts the entire airborne time (when airborne because of jump)
        float INVINCIBILITY_TIME = 1.f; // seconds of jump invincibility after leaving the ground
    }

    // dash parameters
    namespace Dash
    {
        /*
        * false = invincibility does not last the full dash time. invincibility will last for the number of seconds specified in INVINCIBILITY_TIME
        * true  = invincibility lasts full dash time
        */
        bool FULL_DASH_INVINCIBILITY = false; // whether or not dash invincibility lasts the entire duration of the dash
        float INVINCIBILITY_TIME = 1.f; // seconds of dash invincibility after dash begins
        /*
        *          -60 degrees = current stick/d-pad direction
        *         ^
        *        /    -45 degrees = ending direction (with 75% influence)
        *       /    ^
        *      /   _*       _-> -30 degrees = ending direction (with 50% influence)
        *     /  _*     _-**
        *    / _*   _-**
        *   /_* _-**  __--> -15 degrees = ending direction (with 25% influence)
        *  /_-**__--**
        * P--------------> 0 degrees = initial dash direction
        */
        float DEGREE_OF_DI = 0.5f; // percent (as a decimal, between 0.0 and 1.0) of directional influence (DI) allowed over dash direction
        /*
        * example #1:
        *
        * -110 degrees = current stick/d-pad direction
        * ^       -90 degrees = direction used for DI (with max delta = 90)
        *  \      ^
        *   \     |     ^ -60 degrees = direction used for DI (with max delta = 60)
        *    \    |    /
        *     \   |   /  _^ -45 degrees = direction used for DI (with max delta = 45)
        *      \  |  / _*
        *       \ | /_*
        *        \|/*
        *         P--------------> 0 degrees = initial dash direction
        */
        /*
        * example #2
        *         P--------------> 0 degrees = initial dash direction
        *        /|\_
        *       / | \*_
        *      /  |  \ *_
        *     /   |   \  v 45 degrees = direction used for DI (with max delta = 45)
        *    /    |    \
        *   /     |     v 60 degrees = direction used for DI (with max delta = 60)
        *  /      v
        * v       90 degrees = direction used for DI (with max delta = 90)
        * 110 degrees = current stick/d-pad direction
        */
        float MAXIMUM_DI_DELTA = 45.f; // the maximum direction difference allowed for directional influence (DI)
    }
}

// angel dreamcatcher parameters
namespace Angel
{
    // slash attack parameters
    namespace Slash
    {
        // params go here
    }

    // dream attack parameters
    namespace Dream
    {
        // params go here
    }

    // jump parameters
    namespace Jump
    {
        // params go here
    }

    // dash parameters
    namespace Dash
    {
        // params go here
    }
}

// lightning dreamcatcher parameters
namespace Lightning
{
    // slash attack parameters
    namespace Slash
    {
        // params go here
    }

    // dream attack parameters
    namespace Dream
    {
        // params go here
    }

    // jump parameters
    namespace Jump
    {
        // params go here
    }

    // dash parameters
    namespace Dash
    {
        // params go here
    }
}

// shield dreamcatcher parameters
namespace Shield
{
    // slash attack parameters
    namespace Slash
    {
        // params go here
    }

    // dream attack parameters
    namespace Dream
    {
        // params go here
    }

    // jump parameters
    namespace Jump
    {
        // params go here
    }

    // dash parameters
    namespace Dash
    {
        // params go here
    }
}

#endif