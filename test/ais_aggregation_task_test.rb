using_task_library "ais_base"

describe OroGen.ais_base.AISAggregationTask do
    run_live

    attr_reader :task
    before do
        @task = syskit_deploy(
            OroGen.ais_base.AISAggregationTask
                .deployed_as("test_task")
        )
    end

    it "forwards only new position data" do
        t0 = Time.now
        p0 = position(1_234, t0)
        p1 = position(2_468, t0)

        syskit_configure_and_start(@task)
        out =
            expect_execution do
                syskit_write task.vessel_position_in_port, p0, p1
            end.to { have_new_samples(task.vessel_position_port, 2) }

        assert_equal p0, out[0]
        assert_equal p1, out[1]

        p1.time = t0 + 1
        expect_execution do
            syskit_write task.vessel_position_in_port, p0, p1
        end.to do
            have_one_new_sample(task.vessel_position_port)
                .matching { |s| s.mmsi == 2_468}
        end
    end

    it "forwards only new vessel information data" do
        t0 = Time.now
        i0 = information(1_234, t0)
        i1 = information(2_468, t0)

        syskit_configure_and_start(@task)
        out =
            expect_execution do
                syskit_write task.vessel_information_in_port, i0, i1
            end.to { have_new_samples(task.vessel_information_port, 2) }

        assert_equal i0, out[0]
        assert_equal i1, out[1]

        i1.time = t0 + 1
        expect_execution do
            syskit_write task.vessel_information_in_port, i0, i1
        end.to do
            have_one_new_sample(task.vessel_information_port)
                .matching { |s| s.mmsi == 2_468}
        end
    end

    it "forwards only new voyage information data" do
        t0 = Time.now
        voyage0 = voyage_information(1_234, t0)
        voyage1 = voyage_information(2_468, t0)

        syskit_configure_and_start(@task)
        out =
            expect_execution do
                syskit_write task.voyage_information_in_port, voyage0, voyage1
            end.to { have_new_samples(task.voyage_information_port, 2) }

        assert_equal voyage0, out[0]
        assert_equal voyage1, out[1]

        voyage1.time = t0 + 1
        expect_execution do
            syskit_write task.voyage_information_in_port, voyage0, voyage1
        end.to do
            have_one_new_sample(task.voyage_information_port)
                .matching { |s| s.mmsi == 2_468}
        end
    end

    it "does not forward mmsi data in the filter list" do
        task.properties.filtered_mmsi = [2_468, 4_826]
        syskit_configure_and_start(@task)
        t0 = Time.now
        voyage0 = voyage_information(1_234, t0)
        voyage1 = voyage_information(2_468, t0)

        out =
            expect_execution do
                syskit_write task.voyage_information_in_port, voyage1, voyage0
            end.to do
                have_one_new_sample(task.voyage_information_port)
                    .matching { |s| s.mmsi == 1_234 }
            end
    end

    def position(mmsi, time = Time.now)
        Types.ais_base.Position.new(
            time: time,
            mmsi: mmsi
        )
    end

    def information(mmsi, time = Time.now)
        Types.ais_base.VesselInformation.new(
            time: time,
            mmsi: mmsi
        )
    end

    def voyage_information(mmsi, time = Time.now)
        Types.ais_base.VoyageInformation.new(
            time: time,
            mmsi: mmsi
        )
    end
end