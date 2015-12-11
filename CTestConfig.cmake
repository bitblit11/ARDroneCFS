## This file should be placed in the root directory of your project.
## Then modify the CMakeLists.txt file in the root directory of your
## project to incorporate the testing dashboard.
##
## # The following are required to submit to the CDash dashboard:
##   ENABLE_TESTING()
##   INCLUDE(CTest)

set(CTEST_PROJECT_NAME "ARDroneCFS")
set(CTEST_NIGHTLY_START_TIME "00:00:00 EST")

set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "www.windhoverlabs.com")
set(CTEST_DROP_LOCATION "/cdash/submit.php?project=ARDroneCFS")
set(CTEST_DROP_SITE_CDASH TRUE)
set(CTEST_CDASH_VERSION "2.3")
set(CTEST_CDASH_QUERY_VERSION TRUE)