cd app_server/lib
gzip -cd cpptest-1.1.2.tar.gz | tar xvf -   # unpack the sources
cd cpptest-1.1.2                            # change to the its directory
./configure                                 # run the 'configure' script
make                                        # build 'cpptest'
sudo make install
cd ../../../
