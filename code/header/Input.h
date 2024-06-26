#ifndef _PIECEINPUT_H_
#define _PIECEINPUT_H_
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ID.h"

class PieceInput {
private:
    sf::Texture Black_King_Texture;
    sf::Texture Black_Queen_Texture;
    sf::Texture Black_Bishop_Texture;
    sf::Texture Black_Knight_Texture;
    sf::Texture Black_Rook_Texture;
    sf::Texture Black_Pawn_Texture;
    
    sf::Texture White_King_Texture;
    sf::Texture White_Queen_Texture;
    sf::Texture White_Bishop_Texture;
    sf::Texture White_Knight_Texture;
    sf::Texture White_Rook_Texture;
    sf::Texture White_Pawn_Texture;

    sf::Texture Board_Texture;
    sf::Texture RotateBoard_Texture;
    sf::Texture Rotate_Arrow;
    sf::Texture Input_Button;

    sf::Font font;
    sf::Text PlayerTurnText;
    sf::Text Message;

    sf::RectangleShape CommandWindow;
    sf::RectangleShape ManualWindow;
    sf::CircleShape MoveHint;
    sf::RectangleShape CheckSquare;
    sf::RectangleShape PreviousSquare;
    sf::RectangleShape ToSquare;
    
    sf::RectangleShape UndoButton;
    sf::RectangleShape ResetButton;
    sf::Text Undotxt;
    sf::Text Resettxt;

    sf::RectangleShape ManualLine[3];
    sf::Text Manualtext;
    sf::CircleShape ManualButton;
    sf::RectangleShape ManualChosen;
    sf::Texture ManualNextMove;
    sf::Texture ManualPreviousMove;
    sf::Texture ManualPlayButton;
    sf::Texture ManualPauseButton;

    sf::Texture TutorialButton;
    sf::Texture TutorialBoard;
    sf::Texture PieceTutorial;
    sf::Texture PieceSpecialMove;
    sf::Texture RuleTutorial;
    sf::Texture PawnFirstMove;
    sf::Texture Enpassant;
    sf::Texture Promotion;
    sf::Texture Castling;
    sf::Texture Check;
    sf::Texture CheckMate;
    sf::Texture StaleMate;
    sf::Texture MoveRule;

public:
    PieceInput();
    sf::Sprite GetBoard();
    sf::Sprite GetRotateBoard();
    sf::Sprite GetTutorialBoard();
    sf::Sprite GetRotateArrow();
    sf::Sprite GetInputButton();
    sf::RectangleShape GetCommandWindow();
    sf::RectangleShape GetManualWindow();
    sf::RectangleShape GetCheckSquare();
    sf::RectangleShape GetPreviousSquare();
    sf::RectangleShape GetToSquare();
    sf::Sprite GetSprite(ID piece);
    sf::CircleShape GetMoveHint();
    sf::Text GetPlayerTurnText();
    sf::Text GetMessagetext();
    sf::RectangleShape GetUndoButton();
    sf::RectangleShape GetResetButton();
    sf::Text GetUndotxt();
    sf::Text GetResettxt();
    sf::Image GetRandomIcon();

    std::vector<sf::RectangleShape> GetManualLine(int N);
    std::vector<sf::Text> GetManualtext(int N);
    sf::CircleShape GetManualButton();
    sf::RectangleShape GetManualChosen();
    sf::Sprite GetManualNextMoveButton();
    sf::Sprite GetManualPreviousButton();
    sf::Sprite GetManualPlayButton();
    sf::Sprite GetManualPauseButton();

    sf::Sprite GetTutorialButton();
    std::vector<sf::Sprite> GetListButton();
    std::vector<sf::Sprite> GetSpecialMoveButton();
    std::vector<sf::Sprite> GetRuleButton();
};

#endif