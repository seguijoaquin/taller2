cd src

mkdir -p Coverage

lcov --directory ./CMakeFiles --capture --output-file Coverage/coverage.info

cd Coverage

genhtml coverage.info

cd ..

mv -f ./Coverage ../
