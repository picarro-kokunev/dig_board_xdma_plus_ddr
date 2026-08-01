#
# Assign pcie lanes to xcvrs
#

# PCIe Lane 0
set_property LOC GTPE2_CHANNEL_X0Y4 [get_cells -hierarchical -filter "REF_NAME == GTPE2_CHANNEL && NAME =~ *pipe_lane\[0\]*"]
# PCIe Lane 1
set_property LOC GTPE2_CHANNEL_X0Y5 [get_cells -hierarchical -filter "REF_NAME == GTPE2_CHANNEL && NAME =~ *pipe_lane\[1\]*"]
# PCIe Lane 2
set_property LOC GTPE2_CHANNEL_X0Y6 [get_cells -hierarchical -filter "REF_NAME == GTPE2_CHANNEL && NAME =~ *pipe_lane\[2\]*"]
# PCIe Lane 3
set_property LOC GTPE2_CHANNEL_X0Y7 [get_cells -hierarchical -filter "REF_NAME == GTPE2_CHANNEL && NAME =~ *pipe_lane\[3\]*"]
