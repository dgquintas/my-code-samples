#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ucontext.h>

#include <iostream>

// Fugly global var (this is just a proof of concept after all, I get
// to do this). Where a safe state of the program will be saved to.
// The idea is to "save game" right before we face the tricky part of
// the game so that we can restore if we fuckup.
ucontext_t ucp;

// Represents the call to the flaky library.
void FuckYouMaybe() {
    if (rand() % 2) {
        int* nil = 0;
        int woops = *nil;
    }
    if (rand() % 3) {
        int zero = 0;  // using a literal int elicits a warning.
        int lol = 1/zero;
    }
}


// Akin to the "event loop" or whatever is driving the app.
void RollTheDice() {
    srand(time(NULL));
    for (int i=0; i < 10; ++i) {
        assert(!getcontext(&ucp));  // save game!
        FuckYouMaybe();  // then take our chances.
    }
    std::cout << "Ah ah ah ah stayin' alive" << std::endl;
}


////// SIGNALS SHIT /////////
////// Here be dragons //////
/////////////////////////////
// Signal handler. Restored the "savegame" to a known safe state.
void DealWithIt(int signum) {
    std::cerr << "Shit happened: " << strsignal(signum) << std::endl;
    setcontext(&ucp);  // if shit happened, restore our "saved game".
}
// Setup DealWithIt as the signal handlers for a bunch of pretty
// bad signals.
bool SetupSafetyNet() {
    const int sigs[] = {SIGFPE, SIGILL, SIGSEGV, SIGABRT};
    const int n = sizeof(sigs)/sizeof(int);
    struct sigaction sig_act;
    sig_act.sa_handler = DealWithIt;
    for (int i = 0; i < n; ++i) {
        if (sigaction(sigs[i], &sig_act, NULL)) {
            std::cerr << "Couldn't pull it off:\n"
                      << strerror(errno) << std::endl;
            return false;
        }
    }
    std::cerr << "All good. Crash away." << std::endl;
    return true;
}

int main() {
    if (SetupSafetyNet()) {
        RollTheDice();
    } else {
        std::cerr << "Setup failed" << std::endl;
        return 1;
    }
    return 0;
}
