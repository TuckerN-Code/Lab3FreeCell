#include "FreeCellGame.h"

FreeCellGame::FreeCellGame()
{
}

FreeCellGame::FreeCellGame(const FreeCellGame& cpy) :
	m_gameCurrentCard(cpy.m_gameCurrentCard), m_gameFreeCells(cpy.m_gameFreeCells),
	m_gameHomeCells(cpy.m_gameHomeCells), m_gameTableStack(cpy.m_gameTableStack)
{

}

FreeCellGame::FreeCellGame(FreeCellGame&& mv) noexcept :
	m_gameCurrentCard(mv.m_gameCurrentCard), m_gameFreeCells(mv.m_gameFreeCells),
	m_gameHomeCells(mv.m_gameHomeCells), m_gameTableStack(mv.m_gameTableStack)
{
	mv.m_gameCurrentCard = Card();
	mv.m_gameFreeCells = FreeCells();
	mv.m_gameHomeCells = HomeCells();
	mv.m_gameTableStack = TableStack();
}

FreeCellGame::~FreeCellGame()
{
}

FreeCellGame FreeCellGame::operator=(const FreeCellGame& cpy)
{
	m_gameCurrentCard = cpy.m_gameCurrentCard;
	m_gameFreeCells = cpy.m_gameFreeCells;
	m_gameHomeCells = cpy.m_gameHomeCells;
	m_gameTableStack = cpy.m_gameTableStack;
	return *this;
}

void FreeCellGame::runGame()
{
	while (!m_gameHomeCells.checkWin() && m_quit == false)
	{
		refreshBoard();
		std::cout << "- Type (1) to take a card from a table stack -\n" <<
			"- Type (2) to take a card from a free cell -\n"<<
			"- Type (3) to quit -\n";


		takeTurn();

	}
	if (m_gameHomeCells.checkWin())
		endGame();

}

void FreeCellGame::endGame()
{
	refreshBoard();
	std::cout << "- Congrats you won! -";
}

void FreeCellGame::refreshBoard()
{

	std::cout << "------------------\nWelcome to FreeCell\n------------------" << std::endl;
	//std::cout << "Card in hand :   " << m_gameCurrentCard << std::endl;
	m_gameHomeCells.printHomeCells();
	m_gameFreeCells.printFreeCells();
	m_gameTableStack.printTable();

}

void FreeCellGame::takeTurn()
{
	int turn;
	std::cin >> turn;

	switch (turn)
	{
	case 1: //move from table stack 
		std::cout << "Pick the coloum to take the card from: ";
		int pos;
		pos = pickUpCardTable();
		switch (chooseCardDest())
		{
		case 1:
			placeFree(pos, m_gameCurrentCard);
			break;
		case 2:
			placeHome(pos, m_gameCurrentCard);
			break;
		case 3:
			placeTable(pos, m_gameCurrentCard);
			break;
		default:
			badPlaceInputTable(pos, m_gameCurrentCard);
			break;
		}
		break;
	case 2:
		std::cout << "Pick the cell to take the card from: ";
		pos = pickUpCardFree();
		switch (chooseCardDest())
		{
		case 1:
			placeFree(pos, m_gameCurrentCard);
			break;
		case 2:
			placeHome(pos, m_gameCurrentCard);
			break;
		case 3:
			placeTable(pos, m_gameCurrentCard);
			break;
		default:
			badPlaceInputFree(pos, m_gameCurrentCard);
			break;
		}
	case 3:
		m_quit = true;
		break;
	default:
		invalidOption( "bad move input" );
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		break;
	}
}

void FreeCellGame::invalidOption(const char* msg)
{
	std::cout << msg << "\n\n" << std::endl;;
}

void FreeCellGame::placeHome(int pos, Card crd)
{
	try
	{
		if (!m_gameHomeCells.placeCard(crd))
		{
			m_gameTableStack.undoPopCard(crd, pos - 1);
			crd = Card();
		}
	}
	catch (Exception myEx)
	{
		std::cout << "unable to place card\n\n" << std::endl;
		m_gameTableStack.undoPopCard(crd, pos - 1);
		crd = Card();
	}
}

void FreeCellGame::placeTable(int pos, Card crd)
{
	try
	{
		std::cout << "Which coloum do you want to place the card in: ";
		int destPos;
		std::cin >> destPos;
		std::cout << std::endl;

		if (!m_gameTableStack.placeCard(crd, destPos - 1))
		{
			m_gameTableStack.undoPopCard(crd, pos - 1);
			crd = Card();
			invalidOption("Can not place card there");
		}
	}
	catch (Exception myEx)
	{
		std::cout << "unable to place card" << std::endl;
		m_gameTableStack.undoPopCard(crd, pos - 1);
		crd = Card();
	}
}

void FreeCellGame::placeFree(int pos, Card crd)
{
	std::cout << "Which cell do you want to place the card in: ";
	int destPos;
	std::cin >> destPos;
	std::cout << std::endl;
	try
	{
		m_gameFreeCells.placeCard(crd, destPos - 1);
		crd = Card();
	}
	catch (Exception myEx)
	{
		std::cout << "unable to place card\n\n" << std::endl;
		m_gameTableStack.undoPopCard(crd, pos - 1);
		crd = Card();
	}
}

int FreeCellGame::pickUpCardTable()
{
	int pos;
	std::cin >> pos;
	std::cout << std::endl;
	try
	{
		m_gameCurrentCard = m_gameTableStack.popCard(pos - 1);
	}
	catch (Exception myExcpt)
	{
		std::cout << "Unable to remove card" << std::endl;
	}
	return pos;
}

int FreeCellGame::pickUpCardFree()
{
	int pos;
	std::cin >> pos;
	std::cout << std::endl;
	try
	{
		m_gameCurrentCard = m_gameFreeCells.removeCard(pos - 1);
	}
	catch (Exception myExcpt)
	{
		std::cout << "Unable to remove card" << std::endl;
	}
	return pos;
}

int FreeCellGame::chooseCardDest()
{
	std::cout << "place the card 1) free cell 2) home cell 3) table stack: ";
	int dest;
	std::cin >> dest;
	std::cout << std::endl;
	return dest;
}

void FreeCellGame::badPlaceInputTable(int pos, Card crd)
{
	invalidOption("bad place input");
	m_gameTableStack.undoPopCard(crd, pos - 1);
	crd = Card();
}

void FreeCellGame::badPlaceInputFree(int pos, Card crd)
{
	invalidOption("bad place input");
	m_gameFreeCells.placeCard(crd, pos - 1);
	crd = Card();
}



