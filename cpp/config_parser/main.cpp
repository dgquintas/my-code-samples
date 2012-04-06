#include <iostream>
#include <string>

#include "ConfigParser.h"

int main(void)
{
  ConfigsMap cm = ConfigParser::getInstance()->getParsedConfigs("test.cfg");
  

    double mu_pt_lowcut;
    double mtau_lowcut;
    double mtau_highcut;
    double gammamucos_lowcut;  
    bool verbose;
    std::string inrootfile,outrootfile;

    cm["analysis"]["mu_pt_lowcut"].getValue(mu_pt_lowcut);
    cm["analysis"]["mtau_lowcut"].getValue(mtau_lowcut);
    cm["analysis"]["mtau_highcut"].getValue(mtau_highcut);
    cm["analysis"]["gammamucos_lowcut"].getValue(gammamucos_lowcut);         
    cm["analysis"]["inrootfile"].getValue(inrootfile);
    cm["analysis"]["outrootfile"].getValue(outrootfile);

    std::cout << mu_pt_lowcut << std::endl;
    std::cout << mtau_lowcut << std::endl;
    std::cout << mtau_highcut<< std::endl;
    std::cout << gammamucos_lowcut << std::endl;
    std::cout << inrootfile << std::endl;
    std::cout << outrootfile << std::endl;

    std::cout << cm << std::endl;

  return 0;
}
