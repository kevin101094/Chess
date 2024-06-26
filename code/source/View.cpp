#include "View.h"

View::View(sf::RenderWindow& window, Game* game) : MainWindow(window){
	this->game = game;
	input = nullptr;
	BeginX = BeginY = 10;
	gap = 146;
}
void View::Init(bool isRotate) {
	input = new PieceInput();
	Tooltip* oldtip = tooltip;
	tooltip = new Tooltip(MainWindow);
	delete oldtip;
	Update(isRotate);
	Board = input->GetBoard();
	MoveHint = input->GetMoveHint();
	CheckSquare = input->GetCheckSquare();
	PlayerTurnText = input->GetPlayerTurnText();
	Rotate_Button = input->GetRotateArrow();
	Rotate_Button.setScale(0.15, 0.15);
	Rotate_Button.setPosition(1170, 20+ gap*3.5);
	Input_Button = input->GetInputButton();
	Input_Button.setScale(0.15, 0.15);
	Input_Button.setPosition(1200, 880);
	RotateBackground = sf::RectangleShape(sf::Vector2f(65, 75));
	RotateBackground.setPosition(1175, 20 + gap * 3.5+5);
	InputBackground = sf::RectangleShape(sf::Vector2f(70, 70));
	InputBackground.setPosition(1195, 875);
	for(int i=0; i<3; i++) PreviousSquare[i] = input->GetPreviousSquare();
	PreviousSquare[2].setFillColor(sf::Color(207, 207, 207));
	Message = input->GetMessagetext();
	UndoButton = input->GetUndoButton();
	ResetButton = input->GetResetButton();

	ManualLine = input->GetManualLine(9);
	Manualtext = input->GetManualtext(2);
	ManualLeftButton = ManualRightButton = input->GetManualButton();
	ManualLeftButton.rotate(270);
	ManualLeftButton.setPosition(1310, 945);
	ManualRightButton.rotate(90);
	ManualRightButton.setPosition(1730, 885);
	ManualChosen = input->GetManualChosen();
	ManualNextMoveButton = input->GetManualNextMoveButton();
	ManualNextMoveButton.setPosition(1590, 883);
	ManualNextMoveButton.setScale(0.12, 0.12);
	ManualPreviousMoveButton = input->GetManualPreviousButton();
	ManualPreviousMoveButton.setPosition(1390, 883);
	ManualPreviousMoveButton.setScale(0.12, 0.12);
	ManualNextMoveBg = ManualPreviousMoveBg = sf::RectangleShape(sf::Vector2f(40, 70));
	ManualNextMoveBg.setPosition(1600, 879);
	ManualPreviousMoveBg.setPosition(1403, 879);
	ManualPlayButton = input->GetManualPlayButton();
	ManualPlayButton.setPosition(1487, 879);
	ManualPlayButton.setScale(0.118, 0.118);
	ManualPauseButton = input->GetManualPauseButton();
	ManualPauseButton.setPosition(1492, 884);
	ManualPauseButton.setScale(0.1, 0.1);
	ManualPlaybg = sf::RectangleShape(sf::Vector2f(65, 65));
	ManualPlaybg.setPosition(1489, 881);

	TutorialButton = input->GetTutorialButton();
	TutorialButton.setScale(0.25, 0.25);
	TutorialButton.setPosition(1720, 20);
	TutorialBg = sf::RectangleShape(sf::Vector2f(73, 73));
	TutorialBg.setPosition(1715, 15);
}
void View::Update(bool isRotate) {
	BoardControl Board = game->getBoard();
	SpriteItem.clear();
	sf::Sprite sprite;
	sprite.setScale(1, 1);
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			ID pieceID = Board.GetPieceID(r, c);
			if (pieceID == Empty) continue;
			sprite = input->GetSprite(pieceID);
			sprite.setPosition(BeginX + c * gap, BeginY + r * gap);
			if (isRotate)
				sprite.setPosition(BeginX + (7-c) * gap, BeginY + (7 - r) * gap);
			SpriteItem.push_back(sprite);
		}
	}
	if (game->isTurn()) {
		PlayerTurnText.setString("White Turn.");
	}
	else {
		PlayerTurnText.setString("Black Turn.");
	}
}
void View::Draw(bool isDrag, bool isRotate) {
	Board = input->GetBoard();
	if (isRotate) {
		Board = input->GetRotateBoard();
		int X = Board.getPosition().x, Y = Board.getPosition().y;
		Board.setPosition(X - 2, Y);
	}
	MainWindow.draw(Board);
	MainWindow.draw(input->GetCommandWindow());
	DrawText(isRotate);
	PreviousSquare[0].setPosition(game->getLastPrevious().second * gap, game->getLastPrevious().first * gap);
	if(isRotate)
		PreviousSquare[0].setPosition((7-game->getLastPrevious().second) * gap, (7-game->getLastPrevious().first) * gap);
	MainWindow.draw(PreviousSquare[0]);
	PreviousSquare[1].setPosition(game->getLastTo().second * gap, game->getLastTo().first * gap);
	if (isRotate)
		PreviousSquare[1].setPosition((7-game->getLastTo().second) * gap, (7 - game->getLastTo().first) * gap);
	MainWindow.draw(PreviousSquare[1]);
	if (!isDrag) Update(isRotate);
	for (sf::Sprite sprite : SpriteItem) {
		MainWindow.draw(sprite);
	}
}
void View::DrawManual(std::vector<csmData> csmManual, int Manualscroll, int ManualsetID) {
	int Manualblank = 75;
	MainWindow.draw(input->GetManualWindow());
	if (ManualsetID > 0) {
		ManualsetID--;
		ManualChosen.setPosition((1320 + (ManualsetID % 2)*225), 420 + (ManualsetID / 2) * Manualblank);
		MainWindow.draw(ManualChosen);
	}
	for (sf::RectangleShape tmp : ManualLine) {
		MainWindow.draw(tmp);
	}
	Manualtext = input->GetManualtext(8);
	Manualcontent = input->GetManualtext(csmManual.size()*2 + 2);
	int len = ((csmManual.size() - 6 * Manualscroll)) * 2;
	for (int i = 0; i < std::min(len/2, 6); i++) {
		std::string SS;
		SS = std::to_string(Manualscroll * 6 + i + 1);
		Manualtext[i].setString(SS);
		MainWindow.draw(Manualtext[i]);
	}
	MainWindow.draw(Manualtext[6]);
	MainWindow.draw(Manualtext[7]);
	for (int i = 0; i < std::min(len, 12); i++) {
		Manualcontent[i].setCharacterSize(40);
		if (i % 2 == 0) { //white
			if (csmManual[6 * Manualscroll+ i / 2].WhiteMove == "-1") break;
			Manualcontent[i].setPosition(1370, 430 + Manualblank * (i/2));
			Manualcontent[i].setString(csmManual[6 * Manualscroll+ i / 2].WhiteMove);
		}
		else if (i % 2 == 1) { //black
			if (csmManual[6 * Manualscroll+ i / 2].BlackMove == "-1") break;
			Manualcontent[i].setPosition(1600, 430 + Manualblank * (i/2));
			Manualcontent[i].setString(csmManual[6 * Manualscroll+ i / 2].BlackMove);
		}
		MainWindow.draw(Manualcontent[i]);
	}


}

void View::DrawText(bool isRotate) {
	MainWindow.draw(PlayerTurnText);
	Message.setString("");
	if (game->isStaleMate()) {
		Message.setString("StaleMate.");
		if (game->isMove_50())
			Message.setString("StaleMate.\n50 Moves Rule.");
	}
	else if (game->isBlackChecked()) {
		pair BlackKingPos = game->getBlackKingPos();
		CheckSquare.setPosition(BlackKingPos.second * gap, BlackKingPos.first * gap);
		if(isRotate)
			CheckSquare.setPosition((7-BlackKingPos.second) * gap, (7-BlackKingPos.first) * gap);
		MainWindow.draw(CheckSquare);
		if (game->isBlackWin()) {
			Message.setString("White Won.");
		}
		else {
			Message.setString("Black In Check.");
		}
	}
	else if (game->isWhiteChecked()) {
		pair WhiteKingPos = game->getWhiteKingPos();
		CheckSquare.setPosition(WhiteKingPos.second * gap, WhiteKingPos.first * gap);
		if(isRotate)
			CheckSquare.setPosition((7-WhiteKingPos.second) * gap, (7-WhiteKingPos.first) * gap);
		MainWindow.draw(CheckSquare);
		if (game->isWhiteWin()) {
			Message.setString("Black Won.");
		}
		else {
			Message.setString("White In Check.");
		}
	}

	MainWindow.draw(Message);
}
void View::DrawMoveHint(int X, int Y, bool isRotate) {
	BoardControl Board = game->getBoard();
	if (Board.getPieceColor(X, Y) != game->isTurn()) return;
	for (pair tmp : game->getPossibleMove(X,Y)){
		MoveHint.setPosition(42 + BeginY + (tmp.second) * gap, 42 + BeginX + (tmp.first) * gap);
		if(isRotate)
			MoveHint.setPosition(42 + BeginY + (7-tmp.second) * gap, 42 + BeginX + (7-tmp.first) * gap);
		MainWindow.draw(MoveHint);
	}
	PreviousSquare[2].setPosition(Y * gap, X * gap);
	if (isRotate) PreviousSquare[2].setPosition((7 - Y) * gap, (7 - X) * gap);
	MainWindow.draw(PreviousSquare[2]);
}
void View::DrawDragPiece(sf::Sprite& DragPiece) {
	MainWindow.draw(DragPiece);
}
void View::DrawSubWindow(sf::RenderWindow& SubWindow) {
	sf::Sprite sprite;
	PromotionItem.clear();
	sprite.setScale(1, 1);
	ID IDlist[4] = {White_Knight, White_Bishop, White_Rook, White_Queen};
	for (int i = 0; i < 4; i++) {
		sprite = input->GetSprite(IDlist[i]);
		sprite.setPosition(gap * i + gap / 2, gap / 2);
		SubWindow.draw(sprite);
		PromotionItem.push_back(sprite);
	}
}
void View::DrawButton(int X, int Y, bool isPressed, bool isDrag) {
	UndoButton.setFillColor(sf::Color(238, 216, 174));
	ResetButton.setFillColor(sf::Color(238, 216, 174));
	RotateBackground.setFillColor(sf::Color(0, 0, 0, 1));
	InputBackground.setFillColor(sf::Color(0, 0, 0, 1));
	ManualLeftButton.setFillColor(sf::Color(126, 192, 238));
	ManualRightButton.setFillColor(sf::Color(126, 192, 238));
	ManualNextMoveBg.setFillColor(sf::Color(0, 0, 0, 1));
	ManualPreviousMoveBg.setFillColor(sf::Color(0, 0, 0, 1));
	TutorialBg.setFillColor(sf::Color(0, 0, 0, 1));

	if (isInResetButton(X, Y)) {
		ResetButton.setFillColor(sf::Color(255, 231, 186));
		if (isPressed and !isDrag) ResetButton.setFillColor(sf::Color(205, 186, 150));
		if (!isDrag) tooltip->SetTooltip("Reset", 50);
	}
	else if (isInUndoButton(X, Y)) {
		if (isPressed and !isDrag) UndoButton.setFillColor(sf::Color(205, 186, 150));
		else UndoButton.setFillColor(sf::Color(255, 231, 186));
		if (!isDrag) tooltip->SetTooltip("Undo", 50);
	}
	
	if (isInRotateButton(X, Y)) {
		if (isPressed and !isDrag) RotateBackground.setFillColor(sf::Color(190, 190, 190));
		else RotateBackground.setFillColor(sf::Color(211, 211, 211));
		if (!isDrag) tooltip->SetTooltip("Rotate Board", 50);
	}
	else if (isInInputButton(X, Y)) {
		if (isPressed and !isDrag) InputBackground.setFillColor(sf::Color(190, 190, 190));
		else InputBackground.setFillColor(sf::Color(211, 211, 211));
		if (!isDrag) tooltip->SetTooltip("Input Notation", 50);
	}
	else if (isInManualLeftButton(X, Y)) {
		if (isPressed and !isDrag) ManualLeftButton.setFillColor(sf::Color(108, 166, 205));
		else ManualLeftButton.setFillColor(sf::Color(135, 206, 255));
		if (!isDrag) tooltip->SetTooltip("Previous Page", 50);
	}
	else if (isInManualRightButton(X, Y)) {
		if (isPressed and !isDrag) ManualRightButton.setFillColor(sf::Color(108, 166, 205));
		else ManualRightButton.setFillColor(sf::Color(135, 206, 255));
		if (!isDrag) tooltip->SetTooltip("Next Page", 50);
	}
	else if (isInManualNextMoveButton(X, Y)) {
		if (isPressed and !isDrag) ManualNextMoveBg.setFillColor(sf::Color(190, 190, 190));
		else ManualNextMoveBg.setFillColor(sf::Color(211, 211, 211));
		if (!isDrag) tooltip->SetTooltip("Next Move", 50);
	}
	else if (isInManualPreviousMoveButton(X, Y)) {
		if (isPressed and !isDrag) ManualPreviousMoveBg.setFillColor(sf::Color(190, 190, 190));
		else ManualPreviousMoveBg.setFillColor(sf::Color(211, 211, 211));
		if (!isDrag) tooltip->SetTooltip("Previous Move", 50);
	}
	else if (isInTutorialButton(X, Y)) {
		if (isPressed and !isDrag) TutorialBg.setFillColor(sf::Color(190, 190, 190));
		else TutorialBg.setFillColor(sf::Color(211, 211, 211));
		if (!isDrag) tooltip->SetTooltip("Tutorial", 50);
	}
	MainWindow.draw(UndoButton);
	MainWindow.draw(input->GetUndotxt());
	MainWindow.draw(ResetButton);
	MainWindow.draw(input->GetResettxt());
	MainWindow.draw(RotateBackground);
	MainWindow.draw(Rotate_Button);
	MainWindow.draw(InputBackground);
	MainWindow.draw(Input_Button);
	MainWindow.draw(ManualLeftButton);
	MainWindow.draw(ManualRightButton);
	MainWindow.draw(ManualNextMoveBg);
	MainWindow.draw(ManualPreviousMoveBg);
	MainWindow.draw(TutorialBg);
	MainWindow.draw(ManualNextMoveButton);
	MainWindow.draw(ManualPreviousMoveButton);
	MainWindow.draw(TutorialButton);
	tooltip->Draw();
}
void View::DrawManaulPlayButton(int X, int Y, bool isPressed, int isManaulPlay) {
	if (isManaulPlay == -1) return;
	ManualPlaybg.setFillColor(sf::Color(0, 0, 0, 1));
	if (isInManualPlayButton(X, Y, isManaulPlay)) {
		if (isPressed) ManualPlaybg.setFillColor(sf::Color(190, 190, 190));
		else ManualPlaybg.setFillColor(sf::Color(211, 211, 211));
	}
	MainWindow.draw(ManualPlaybg);
	if (isManaulPlay==1) {
		MainWindow.draw(ManualPauseButton);
		if(isInManualPlayButton(X,Y,isManaulPlay)) tooltip->SetTooltip("Pause", 50);
	}
	else {
		MainWindow.draw(ManualPlayButton);
		if(isInManualPlayButton(X,Y,isManaulPlay)) tooltip->SetTooltip("Play", 50);
	}
	tooltip->Draw();
}
std::vector<sf::Sprite>& View::getSpriteItem() {
	return SpriteItem;
}
std::vector<sf::Sprite>& View::getPromotionItem() {
	return PromotionItem;
}
bool View::isInResetButton(int X, int Y) {
	return ResetButton.getGlobalBounds().contains(X, Y);
}
bool View::isInUndoButton(int X, int Y) {
	return UndoButton.getGlobalBounds().contains(X, Y);
}
bool View::isInRotateButton(int X, int Y) {
	return Rotate_Button.getGlobalBounds().contains(X, Y);
}
bool View::isInInputButton(int X, int Y) {
	return Input_Button.getGlobalBounds().contains(X, Y);
}
bool View::isInManualLeftButton(int X, int Y) {
	return ManualLeftButton.getGlobalBounds().contains(X, Y);
}
bool View::isInManualRightButton(int X, int Y) {
	return ManualRightButton.getGlobalBounds().contains(X, Y);
}
int View::isInManualWindow(int X, int Y) {
	//1320 1545 1770
	//420 870
	if (X < 1320 || X>1770 || Y < 420 || Y>870) return 0;
	int Manualblank = 75;
	return (Y - 420) / Manualblank * 2 + ((X - 1320) / 225)+1;
}
bool View::isInManualNextMoveButton(int X, int Y) {
	return ManualNextMoveButton.getGlobalBounds().contains(X, Y);
}
bool View::isInManualPreviousMoveButton(int X, int Y) {
	return ManualPreviousMoveButton.getGlobalBounds().contains(X, Y);
}
bool View::isInManualPlayButton(int X, int Y, int isManualPlay) {
	if (isManualPlay) {
		return ManualPauseButton.getGlobalBounds().contains(X, Y);
	}
	else {
		return ManualPauseButton.getGlobalBounds().contains(X, Y);
	}
}
bool View::isInTutorialButton(int X, int Y) {
	return TutorialButton.getGlobalBounds().contains(X, Y);
}