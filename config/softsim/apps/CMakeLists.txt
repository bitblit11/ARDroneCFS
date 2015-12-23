# Build each application and associated table(s)
add_subdirectory(cfs_lib cfs_lib)
add_subdirectory(cf cf)
add_subdirectory(ci ci)
add_subdirectory(cs cs)
add_subdirectory(ds ds)
add_subdirectory(fm fm)
add_subdirectory(hk hk)
add_subdirectory(hs hs)
add_subdirectory(lc lc)
add_subdirectory(md md)
add_subdirectory(mm mm)
#add_subdirectory(sbn sbn)
add_subdirectory(sc sc)
add_subdirectory(sch sch)
#add_subdirectory(to to)

# Add target to generate all documentation.
add_custom_target(docs
    COMMENT "Generating all documentation." VERBATIM
	COMMAND make cfe-docs
	COMMAND make cf-docs
	COMMAND make cs-docs
	COMMAND make ds-docs
	COMMAND make fm-docs
	COMMAND make hk-docs
	COMMAND make hs-docs
	COMMAND make lc-docs
	COMMAND make md-docs
	COMMAND make mm-docs
	COMMAND make sc-docs
	COMMAND make sch-docs
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/
)
