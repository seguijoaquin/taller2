cd build

mkdir -p Coverage

lcov --directory ./CMakeFiles --capture --output-file Coverage/coverage.info

cd Coverage

genhtml coverage.info
