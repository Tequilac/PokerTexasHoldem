#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "button.h"
#include "decisions.h"
#include "sort.h"
#include "card.h"
#include "combinations.h"
#include "table.h"
#include "deck.h"
#include "actions.h"

enum GameState
{
	Blinds,
	GiveCards,
	Preflop,
	DecisionPlayer,
	Flop,
	FlopBidding,
	Turn,
	TurnBidding,
	River,
	RiverBidding,
	EndOfRound,
	Wait
};



int main()
{
	Random::init();
	Deck deck;
	PlayerHand players[6] = { };
	int moneyOnTable = 0;
	int highestBet = 0;
	bool raisedBet = false;
	int dealer = 0;
	int betting;
	bool givenCards = false;
	bool someoneBid = false;
	bool playerInput = false;
	int raisedBy = 0;
	int winner;
	std::vector<int> winners;

	int windowWidth = sf::VideoMode::getDesktopMode().width;
	int windowHeight = sf::VideoMode::getDesktopMode().height;

	Table table;
	
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Poker Texas Holdem", sf::Style::Fullscreen);
	sf::Color background = sf::Color(0, 102, 0, 255);
	
	
	sf::Texture textures[12];
	sf::Sprite sprites[12];
	sf::Texture tableTextures[5];
	sf::Sprite tableSprites[5];
	

	sf::Texture dealerTexture;
	dealerTexture.loadFromFile("res/dealer.png");
	sf::Sprite dealerSprite;
	dealerSprite.setTexture(dealerTexture);
	dealerSprite.setScale(3.0f, 3.0f);

	float dealerPositions[12] = {	105, 350,
									945, 170,
									1785, 350,
									1785, 890,
									945, 850,
									105, 890 };
	for (int i = 0; i < 6; i++)
	{
		dealerPositions[i * 2] *= (float)windowWidth / 1920;
		dealerPositions[i * 2 + 1] *= (float)windowHeight / 1080;
	}
	dealerSprite.setPosition(dealerPositions[dealer * 2], dealerPositions[dealer * 2 + 1]);


	
	sf::Font arial;
	arial.loadFromFile("res/arial.ttf");

	
	sf::Text playersMoney[6];
	float moneyPositions[12] = {	250, 190,
									850, 180,
									1600, 190,
									1600, 730,
									850, 860,
									250, 730 };
	for (int i = 0; i < 6; i++)
	{
		moneyPositions[i * 2] *= (float)windowWidth / 1920;
		moneyPositions[i * 2 + 1] *= (float)windowHeight / 1080;
	}
	for(int i = 0; i < 6; i ++)
	{
		playersMoney[i].setString(std::to_string(players[i].getMoney()));
		playersMoney[i].setFont(arial);
		playersMoney[i].setFillColor(sf::Color::White);
		playersMoney[i].setPosition(moneyPositions[i * 2], moneyPositions[i * 2 + 1]);
	}

	
	sf::Text playersMoneyBid[6];
	float moneyBidPositions[12] = {	400, 190,
										850, 240,
										1500, 190,
										1500, 730,
										850, 800,
										400, 730 };
	for (int i = 0; i < 6; i++)
	{
		moneyBidPositions[i * 2] *= (float)windowWidth / 1920;
		moneyBidPositions[i * 2 + 1] *= (float)windowHeight / 1080;
	}
	for (int i = 0; i < 6; i++)
	{
		playersMoneyBid[i].setString(std::to_string(players[i].getMoneyBid()));
		playersMoneyBid[i].setFont(arial);
		playersMoneyBid[i].setFillColor(sf::Color::White);
		playersMoneyBid[i].setPosition(moneyBidPositions[i * 2], moneyBidPositions[i * 2 + 1]);
	}

	
	sf::Text moneyText;
	moneyText.setString("Money on table: " + std::to_string(moneyOnTable));
	moneyText.setFont(arial);
	moneyText.setFillColor(sf::Color::White);
	moneyText.setPosition((float)(800 * windowWidth / 1920), (float)(400 * windowHeight / 1080));


	sf::String input = "";
	Button inputText(90, 25, 1090, 940, std::string(""), arial);
	Button confirmButton(90, 25, 1090, 1000, std::string("Confirm"), arial);

	
	Button foldButton(90, 25, 1090 * windowWidth / 1920, 910 * windowHeight / 1080, std::string("Fold"), arial);
	Button callButton(90, 25, 1090 * windowWidth / 1920, 940 * windowHeight / 1080, std::string("Call"), arial);
	Button raiseButton(90, 25, 1090 * windowWidth / 1920, 970 * windowHeight / 1080, std::string("Raise"), arial);
	Button checkButton(90, 25, 1090 * windowWidth / 1920, 1000 * windowHeight / 1080, std::string("Check"), arial);

	GameState gameState = Blinds;
	GameState lastState = Wait;
	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
		}
		window.clear(background);
		switch (gameState)
		{
		case Blinds:
			blinds(players, dealer, highestBet, someoneBid);
			clock.restart();
			gameState = Wait;
			lastState = Blinds;
			break;
		case GiveCards:
			giveCards(deck, players);
			loadSprites(textures, sprites, players, false, windowWidth, windowHeight);
			givenCards = true;
			gameState = Wait;
			lastState = GiveCards;
			break;
		case Preflop:
			winners = determineIfSomeoneWon(players, table);
			if (winners[0] != -1)
				gameState = EndOfRound;
			else if(allPassedOrEqual(players, highestBet))
			{
				gameState = Wait;
				lastState = Preflop;
			}
			else if (betting == 4 && !players[4].getPassed() && !players[4].getOutOfGame())
			{
				gameState = DecisionPlayer;
				lastState = Preflop;
			}
			else
			{
				preflopMakeDecision(players[betting], highestBet, raisedBet, raisedBy);
				betting = (betting + 1) % 6;
			}
			loadSprites(textures, sprites, players, false, windowWidth, windowHeight);
			break;
		case DecisionPlayer:
			if(!playerInput)
			{
				foldButton.draw(window);
				callButton.draw(window);
				raiseButton.draw(window);
				if (!someoneBid)
					checkButton.draw(window);
				if (foldButton.checkForClick())
				{
					doAction(players[4], 0, highestBet, raisedBet, raisedBy, someoneBid);
					gameState = lastState;
					betting = (betting + 1) % 6;
				}
				if (callButton.checkForClick() && highestBet - players[4].getMoneyBid() <= players[4].getMoney())
				{
					doAction(players[4], 1, highestBet, raisedBet, raisedBy, someoneBid);
					gameState = lastState;
					betting = (betting + 1) % 6;
				}
				if (raiseButton.checkForClick())
				{
					playerInput = true;
				}
				if (!someoneBid && checkButton.checkForClick())
				{
					doAction(players[4], 2, highestBet, raisedBet, raisedBy, someoneBid);
					gameState = lastState;
					betting = (betting + 1) % 6;
				}
			}
			else
			{
				if (event.type == sf::Event::TextEntered && event.text.unicode < 58 && event.text.unicode > 47 && input.getSize() < 9 && clock.getElapsedTime().asMilliseconds() > 200)
				{
					input += event.text.unicode;
					inputText.setText(input);
					clock.restart();
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && clock.getElapsedTime().asMilliseconds() > 200)
				{
					input.erase(input.getSize() - 1);
					inputText.setText(input);
					clock.restart();
				}
				inputText.draw(window);
				confirmButton.draw(window);
				if(confirmButton.checkForClick())
				{
					int raise = std::stoi(input.toAnsiString());
					if(raise < players[4].getMoney() && raise >= highestBet + raisedBy)
					{
						doAction(players[4], raise, highestBet, raisedBet, raisedBy, someoneBid);
						input = "";
						inputText.setText(input);
						playerInput = false;
						gameState = lastState;
						betting = (betting + 1) % 6;
					}
					else
					{
						input = "";
						inputText.setText(input);
					}
				}
			}
			break;
		case Flop:
			table.putFlop(deck);
			table.loadTable(tableTextures, tableSprites, windowWidth, windowHeight);
			gameState = Wait;
			lastState = Flop;
			break;
		case FlopBidding:
			winners = determineIfSomeoneWon(players, table);
			if (winners[0] != -1)
				gameState = EndOfRound;
			else if (allPassedOrEqual(players, highestBet) && someoneBid)
			{
				gameState = Wait;
				lastState = FlopBidding;
			}
			else if (betting == 4 && !players[4].getPassed() && !players[4].getOutOfGame())
			{
				gameState = DecisionPlayer;
				lastState = FlopBidding;
			}
			else
			{
				if(!players[betting].getOutOfGame())
					flopMakeDecision(table, players[betting], highestBet, raisedBet, raisedBy, someoneBid);
				betting = (betting + 1) % 6;
			}
			loadSprites(textures, sprites, players, false, windowWidth, windowHeight);
			break;
		case Turn:
			table.putTurn(deck);
			table.loadTable(tableTextures, tableSprites, windowWidth, windowHeight);
			gameState = Wait;
			lastState = Turn;
			break;
		case TurnBidding:
			winners = determineIfSomeoneWon(players, table);
			if (winners[0] != -1)
				gameState = EndOfRound;
			else if (allPassedOrEqual(players, highestBet) && someoneBid)
			{
				gameState = Wait;
				lastState = TurnBidding;
			}
			else if (betting == 4 && !players[4].getPassed() && !players[4].getOutOfGame())
			{
				gameState = DecisionPlayer;
				lastState = TurnBidding;
			}
			else
			{
				if (!players[betting].getOutOfGame())
					flopMakeDecision(table, players[betting], highestBet, raisedBet, raisedBy, someoneBid);
				betting = (betting + 1) % 6;
			}
			loadSprites(textures, sprites, players, false, windowWidth, windowHeight);
			break;
		case River:
			table.putRiver(deck);
			table.loadTable(tableTextures, tableSprites, windowWidth, windowHeight);
			gameState = Wait;
			lastState = River;
			break;
		case RiverBidding:
			if (allPassedOrEqual(players, highestBet) && someoneBid)
			{
				gameState = Wait;
				lastState = RiverBidding;
			}
			else if (betting == 4 && !players[4].getPassed() && !players[4].getOutOfGame())
			{
				gameState = DecisionPlayer;
				lastState = RiverBidding;
			}
			else
			{
				if (!players[betting].getOutOfGame())
					flopMakeDecision(table, players[betting], highestBet, raisedBet, raisedBy, someoneBid);
				betting = (betting + 1) % 6;
			}
			break;
		case EndOfRound:
			winners = determineIfSomeoneWon(players, table);
			transferMoneyToTable(players, moneyOnTable);
			transferMoneyToWinners(players, winners, moneyOnTable);
			loadSprites(textures, sprites, players, true, windowWidth, windowHeight);
			for (PlayerHand& player : players)
				if (player.getMoney() == 0)
					player.setOutOfGame(true);
			gameState = Wait;
			lastState = EndOfRound;
			clock.restart();
			break;
		case Wait:
			switch (lastState)
			{
			case Blinds:
				if(clock.getElapsedTime().asMilliseconds() > 2000)
				{
					gameState = GiveCards;
					lastState = Wait;
				}
				break;
			case GiveCards:
				betting = (dealer + 3) % 6;
				gameState = Preflop;
				lastState = Wait;
				break;
			case Preflop:
				betting = (dealer + 1) % 6;
				raisedBet = false;
				raisedBy = 0;
				gameState = Flop;
				lastState = Wait;
				playerInput = false;
				break;
			case Flop:
				gameState = FlopBidding;
				lastState = Wait;
				raisedBet = false;
				raisedBy = 0;
				transferMoneyToTable(players, moneyOnTable);
				highestBet = 2 * moneyOnTable / 3;
				someoneBid = false;
				break;
			case FlopBidding:
				gameState = Turn;
				lastState = Wait;
				playerInput = false;
				break;
			case Turn:
				gameState = TurnBidding;
				lastState = Wait;
				raisedBet = false;
				raisedBy = 0;
				transferMoneyToTable(players, moneyOnTable);
				highestBet = moneyOnTable / 2;
				someoneBid = false;
				break;
			case TurnBidding:
				gameState = River;
				lastState = Wait;
				playerInput = false;
				break;
			case River:
				gameState = RiverBidding;
				lastState = Wait;
				raisedBet = false;
				raisedBy = 0;
				transferMoneyToTable(players, moneyOnTable);
				highestBet = moneyOnTable / 2;
				someoneBid = false;
				break;
			case RiverBidding:
				gameState = EndOfRound;
				lastState = Wait;
				playerInput = false;
				break;
			case EndOfRound:
				if(clock.getElapsedTime().asMilliseconds() > 4000)
				{
					dealer = (dealer + 1) % 6;
					dealerSprite.setPosition(dealerPositions[dealer * 2], dealerPositions[dealer * 2 + 1]);
					for (PlayerHand& player : players)
						player.setPassed(false);
					someoneBid = false;
					raisedBet = false;
					raisedBy = 0;
					givenCards = false;
					highestBet = 0;
					deck.refill();
					table.makeEmpty();
					gameState = Blinds;
					lastState = Wait;
					break;
				}
				
			}
		}
		if(givenCards)
			for(int i = 0; i < 12; i++)
				if(!players[i/2].getOutOfGame())
					window.draw(sprites[i]);
		for (int i = 0; i < table.getSize(); i++)
			window.draw(tableSprites[i]);
		window.draw(dealerSprite);
		for (int i = 0; i < 6; i++)
		{
			playersMoney[i].setString(std::to_string(players[i].getMoney()));
			window.draw(playersMoney[i]);
			playersMoneyBid[i].setString(std::to_string(players[i].getMoneyBid()));
			window.draw(playersMoneyBid[i]);
		}
		window.draw(moneyText);
		moneyText.setString("Money on table: " + std::to_string(moneyOnTable));
		window.display();
	}
	return 0;
}