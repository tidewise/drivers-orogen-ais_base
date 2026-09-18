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

    m_mmsi_filter = _filtered_mmsi.get();

    return true;
}

bool AISAggregationTask::startHook()
{
    if (!AISAggregationTaskBase::startHook())
        return false;

    for (auto& table : m_tables) {
        table.clear();
    }

    return true;
}

template <typename T>
void forward(RTT::InputPort<T>& in,
    RTT::OutputPort<T>& out,
    std::vector<int32_t> const& mmsi_filter,
    std::unordered_map<int32_t, base::Time>& time_table)
{
    T data;
    while (in.read(data) == RTT::NewData) {
        if (std::find(mmsi_filter.begin(), mmsi_filter.end(), data.mmsi) !=
            mmsi_filter.end()) {
            continue;
        }

        if (data.time > time_table[data.mmsi]) {
            time_table[data.mmsi] = data.time;
            out.write(data);
        }
    }
}

void AISAggregationTask::updateHook()
{
    AISAggregationTaskBase::updateHook();

    forward(_vessel_position_in, _vessel_position, m_mmsi_filter, m_tables[0]);
    forward(_vessel_information_in, _vessel_information, m_mmsi_filter, m_tables[1]);
    forward(_voyage_information_in, _voyage_information, m_mmsi_filter, m_tables[2]);
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
