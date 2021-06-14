#ifndef AUDIO_H
#define AUDIO_H

/*Class Forward Declarations*/
sf::SoundBuffer;
sf::Sound;
sf::Music;

class Audio
{
private:
	/*Sound & Music Variables*/
	bool sound_1_music_0;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::Music music; 

	float volumeCounter;
	bool fadeIn;
	bool fadeOut;

	/*Initializers*/
	void initVariables(const bool& sound_1_music_0, std::string file_path);
public:
	/*Constructor & Destructor*/
	Audio(const bool& sound_0_music_1, std::string file_path);
	virtual ~Audio();

	/*Setters*/
	void setFadeIn(bool fade_in);
	void setFadeOut(bool fade_out);
	void setLoop(bool true_false);
	void setVolume(float volume_level);
	void setPlayOffset(float play_offset);
	void setPitch(float pitch_amount);

	/*Play/Pause/Stop Functions*/
	void play();
	void pause();
	void stop();

	/*Update Functions*/
	void updateFadeOut();
	void updateFadeIn();
	void update();
};
#endif
