#include "GameOverState.h"
#include "NewGame.h"
#include "MainMenu.h"
#include "Highscores.h"


GameOverState::GameOverState(gameDataRef data, int score) : _data(data) {
	this->_score.setString(to_string(score));
}

void GameOverState::Init() {

	Highscores highscore = Highscores(_data);
	highscore.loadHighscores();
	string tempScore = this->_score.getString();
	this->highscoreNumber = highscore.checkHighscores(stoi(tempScore));

	this->_data->assets.loadTexture("Window", PAUSE_WINDOW_PATH);

	this->_Window.setTexture(this->_data->assets.getTexture("Window"));
	this->_Window.setPosition({ SCREEN_WIDTH / 2 - _Window.getGlobalBounds().width / 2  , SCREEN_HEIGHT / 2 - _Window.getGlobalBounds().height / 2 });

	this->_shadow.setFillColor(Color(199, 199, 200, 2.5));
	this->_shadow.setSize({ SCREEN_WIDTH, SCREEN_HEIGHT });

	this->_data->assets.loadFont("Font", MAIN_FONT_PATH);

	this->_retry.setFont(this->_data->assets.getFont("Font"));
	this->_home.setFont(this->_data->assets.getFont("Font"));
	this->_scoreTitle.setFont(this->_data->assets.getFont("Font"));
	this->_score.setFont(this->_data->assets.getFont("Font"));
	this->_recordTitle.setFont(this->_data->assets.getFont("Font"));
	this->_record.setFont(this->_data->assets.getFont("Font"));
	this->_newRecord.setFont(this->_data->assets.getFont("Font"));
	this->_GO.setFont(this->_data->assets.getFont("Font"));

	this->_retry.setCharacterSize(NORMAL);
	this->_home.setCharacterSize(NORMAL);
	this->_scoreTitle.setCharacterSize(NORMAL);
	this->_score.setCharacterSize(NORMAL);
	this->_recordTitle.setCharacterSize(NORMAL);
	this->_record.setCharacterSize(NORMAL);
	this->_newRecord.setCharacterSize(NORMAL);
	this->_GO.setCharacterSize(HEADLINE * 0.8);
	
	this->_GO.setString("GameOver");
	this->_GO.setStyle(Text::Underlined);
	this->_retry.setString("Retry");
	this->_home.setString("Home");
	this->_scoreTitle.setString("Score:");
	this->_recordTitle.setString("Record:");
	this->_record.setString(to_string(highscore.getHighscore()));
	if (this->highscoreNumber > 0) {
		string temp = "Record #" + to_string(highscoreNumber);
		string temp2 = " Beated!";
		this->_newRecord.setString(temp + temp2);
	}
	else if (this->highscoreNumber == 0) {
		this->_newRecord.setString(" ");
	}

	this->_retry.setPosition(_Window.getPosition().x + _Window.getGlobalBounds().width / 4 - _retry.getGlobalBounds().width /2, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.8);
	this->_home.setPosition(_Window.getPosition().x + (_Window.getGlobalBounds().width / 4 * 3) - _home.getGlobalBounds().width / 2, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.8);
	this->_GO.setPosition(_Window.getPosition().x + _Window.getGlobalBounds().width / 2 - _GO.getGlobalBounds().width / 2, _Window.getPosition().y + 1);
	this->_scoreTitle.setPosition(_Window.getPosition().x + _Window.getGlobalBounds().width* 0.4 - _scoreTitle.getGlobalBounds().width / 2, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.3);
	this->_score.setPosition(_scoreTitle.getGlobalBounds().left + _scoreTitle.getGlobalBounds().width, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.3);
	this->_recordTitle.setPosition(_Window.getPosition().x + _Window.getGlobalBounds().width * 0.4 - _recordTitle.getGlobalBounds().width / 2, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.5);
	this->_record.setPosition(_recordTitle.getPosition().x + _recordTitle.getGlobalBounds().width, _Window.getPosition().y + _Window.getGlobalBounds().height * 0.5);
	this->_newRecord.setPosition(_Window.getPosition().x + _Window.getGlobalBounds().width / 2 - _newRecord.getGlobalBounds().width /2 , _Window.getPosition().y + _Window.getGlobalBounds().height * 0.6);
	
	

}
void GameOverState::HandleInput() {

	Event eve;
	while (this->_data->window.pollEvent(eve)) {
		if (Event::Closed == eve.type)
			this->_data->window.close();
		if (Event::MouseButtonPressed == eve.type)
		{
			if (this->_data->input.isTextClicked(_retry, Mouse::Button::Left, this->_data->window))
				this->_data->state.isAdding(stateRef(new NewGame(_data)));
			if (this->_data->input.isTextClicked(_home, Mouse::Button::Left, this->_data->window)) {
				this->_data->state.isAdding(stateRef(new MainMenu(_data)));
			}
		}
	}

}
void GameOverState::Update(float dt) {

	if (this->_data->input.isTextCollide(_retry, this->_data->window)) {
		this->_retry.setFillColor(Color::Cyan);
	}
	else if (this->_data->input.isTextCollide(_home, this->_data->window)) {
		this->_home.setFillColor(Color::Cyan);
	}
	else {
		this->_retry.setFillColor(Color::White);
		this->_home.setFillColor(Color::White);
	}

}
void GameOverState::Draw(float dt) {

	this->_data->window.draw(this->_shadow);
	this->_data->window.draw(this->_Window);
	this->_data->window.draw(this->_GO);
	this->_data->window.draw(this->_home);
	this->_data->window.draw(this->_retry);
	this->_data->window.draw(this->_record);
	this->_data->window.draw(this->_recordTitle);
	this->_data->window.draw(this->_newRecord);
	this->_data->window.draw(this->_score);
	this->_data->window.draw(this->_scoreTitle);
	this->_data->window.display();

}
