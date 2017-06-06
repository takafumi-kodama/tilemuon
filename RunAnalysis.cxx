#include "AnalysisSkeleton.hxx"

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <string>

int 
main(int argc, char* argv[])
{
  std::string fileName("");  
  int c;

  while ( (c = getopt(argc, argv, "I:") ) !=-1 ) {
    switch (c) {
    case 'I':
      fileName = optarg;
      break;
    default: // default block
      break;
    }  
  }
  
  if (fileName.empty()) {
    std::cout << "please specify fileName with -I" << std::endl;
    return EXIT_FAILURE;
  }
  
  TChain myChain("tree");
  myChain.AddFile(fileName.c_str());
  AnalysisSkeleton as(&myChain);
  as.Loop();
  
  return EXIT_SUCCESS;
}

