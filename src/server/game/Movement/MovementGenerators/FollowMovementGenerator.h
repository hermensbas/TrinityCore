/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TRINITY_FOLLOWMOVEMENTGENERATOR_H
#define TRINITY_FOLLOWMOVEMENTGENERATOR_H

#include "AbstractFollower.h"
#include "MovementDefines.h"
#include "MovementGenerator.h"
#include "Optional.h"
#include "Position.h"
#include "Timer.h"

class PathGenerator;
class Unit;

class FollowMovementGenerator : public MovementGenerator, public AbstractFollower
{
    public:
        explicit FollowMovementGenerator(Unit* target, float range, ChaseAngle angle);
        ~FollowMovementGenerator();

        void Initialize(Unit*) override;
        void Reset(Unit*) override;
        bool Update(Unit*, uint32) override;
        void Deactivate(Unit*) override;
        void Finalize(Unit*, bool, bool) override;
        MovementGeneratorType GetMovementGeneratorType() const override { return FOLLOW_MOTION_TYPE; }
        void UnitSpeedChanged() override { _lastTargetPosition.reset(); }
        bool PositionOkay(Unit* target, bool isPlayerPet, bool& targetIsMoving, uint32 diff);

    private:
        void UpdatePetSpeed(Unit* owner);

    private:
        std::unique_ptr<PathGenerator> _path;
        TimeTracker _recheckPredictedDistanceTimer;
        bool _recheckPredictedDistance;
        
        Optional<Position> _lastTargetPosition;
        Optional<Position> _lastPredictedPosition;

        float const _range;
        ChaseAngle const _angle;
};

#endif
