#define DOCTEST_CONFIG_IMPLEMENT
#define _CRTDBG_MAP_ALLOC

#include "doctest.h"
#include "memdebug.h"
#include "FreeCellGame.h"

#include <crtdbg.h>

int main(int argc, char** argv) {
    // INITIALIZE LEAK REPORT AT EXIT AND WRITE IN CONSOLE WINDOW
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

    // Setup DocTest and run the tests
    doctest::Context context;
    context.setOption("abort-after", 1);              // stop test execution after 1 failed assertions
    context.applyCommandLine(argc, argv);
    int res = context.run(); // run
    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests


    // your program - if the testing framework is integrated in your production code
    int client_stuff_return_code = 0;
   

    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}

TEST_CASE("Create Cards")
{
    Card cardOne;
    CHECK(cardOne.getSuite() == 0);
    CHECK(cardOne.getValue() == 0);

    Card cardTwo(3, 5);

    CHECK(cardTwo.getSuite() == 3);
    CHECK(cardTwo.getValue() == 5);
}

TEST_CASE("Create Deck")
{
    Deck deckOne;

    //deckOne.printDeck();

    CHECK(deckOne.getCard(0).getSuite() == 1);
    CHECK(deckOne.getCard(0).getValue() == 1);
    CHECK(deckOne.getCard(51).getSuite() == 4);
    CHECK(deckOne.getCard(51).getValue() == 13);

    deckOne.shuffle();
    //deckOne.printDeck();
    // can't fully check deck
}
#if 0
TEST_CASE("TableStack")
{
    TableStack testTable;
    HomeCells testCells;
    FreeCells testFreeCells;

    testCells.placeCard(Card(1, 1));
    testCells.printHomeCells();

    testFreeCells.placeCard(Card(1, 3), 2);
    testFreeCells.printFreeCells();

    testTable.printTable();
}
#endif

TEST_CASE("FreeCellGame")
{
    FreeCellGame testFreeCellGame;

    testFreeCellGame.runGame();
}