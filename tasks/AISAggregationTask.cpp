/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "AISAggregationTask.hpp"

using namespace ais_base;

AISAggregationTask::AISAggregationTask(std::string const& name)
    : AISAggregationTaskBase(name)
{
}

AISAggregationTask::~AISAggregationTask()
{
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See AISAggregationTask.hpp for more detailed
// documentation about them.

bool AISAggregationTask::configureHook()
{
    if (!AISAggregationTaskBase::configureHook())
        return false;
    return true;
}
bool AISAggregationTask::startHook()
{
    if (!AISAggregationTaskBase::startHook())
        return false;
    return true;
}
void AISAggregationTask::updateHook()
{
    AISAggregationTaskBase::updateHook();
}
void AISAggregationTask::errorHook()
{
    AISAggregationTaskBase::errorHook();
}
void AISAggregationTask::stopHook()
{
    AISAggregationTaskBase::stopHook();
}
void AISAggregationTask::cleanupHook()
{
    AISAggregationTaskBase::cleanupHook();
}
