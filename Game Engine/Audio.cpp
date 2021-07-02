#include "Header.h"
#include "Audio.h"

/*Initializers*/
void Audio::initVariables(const bool& sound_1_music_0, std::string file_path)
{
	this->sound_1_music_0 = sound_1_music_0;

	if (this->sound_1_music_0)
	{
		if (!this->soundBuffer.loadFromFile(file_path))
			throw ("ERROR::AUDIO::FAILED_TO_LOAD SOUND_BUFFER::void Audio::initVariables(bool sound_0_music_1, std::string file_path)");

		this->sound.setBuffer(this->soundBuffer);
	}
	else if (!this->sound_1_music_0)
	{

		if (!music.openFromFile(file_path))
			throw ("ERROR::AUDIO::FAILED_TO_LOAD MUSIC::void Audio::initVariables(bool sound_0_music_1, std::string file_path)");
	}

	this->volumeCounter = 0.f;
	this->fadeIn = false;
	this->fadeOut = false;
}

/*Constructor & Destructor*/
Audio::Audio(const bool& sound_0_music_1, std::string file_path)
{
	this->initVariables(sound_0_music_1, file_path);
}
Audio::~Audio()
{
}

/*Setters*/
void Audio::setFadeIn(bool fade_in)
{
	this->fadeIn = fade_in;
}
void Audio::setFadeOut(bool fade_out)
{
	this->fadeOut = fade_out;
}
void Audio::setLoop(bool true_false)
{
	if (this->sound_1_music_0)
	{
		this->sound.setLoop(true_false);
	}
	else if (!this->sound_1_music_0)
	{
		this->music.setLoop(true_false);
	}
}
void Audio::setVolume(float volume_level)
{
	if (this->sound_1_music_0)
	{
		this->sound.setVolume(volume_level);
	}
	else if (!this->sound_1_music_0)
	{
		this->music.setVolume(volume_level);
	}
}
void Audio::setPlayOffset(float play_offset)
{
	if (this->sound_1_music_0)
	{
		this->sound.setPlayingOffset(sf::seconds(play_offset));
	}
	else if (!this->sound_1_music_0)
	{
		this->music.setPlayingOffset(sf::seconds(play_offset));
	}
}
void Audio::setPitch(float pitch_amount)
{
	if (this->sound_1_music_0)
	{
		this->sound.setPitch(pitch_amount);
	}
	else if (!this->sound_1_music_0)
	{
		this->music.setPitch(pitch_amount);
	}
}

/*Play/Pause/Stop Functions*/
void Audio::play()
{
	if (this->sound_1_music_0)
	{
		this->sound.play();
	}
	else if (!this->sound_1_music_0)
	{
		this->music.play();
	}
}
void Audio::pause()
{
	if (this->sound_1_music_0)
	{
		this->sound.pause();
	}
	else if (!this->sound_1_music_0)
	{
		this->music.pause();
	}
}
void Audio::stop()
{
	if (this->sound_1_music_0)
	{
		this->sound.stop();
	}
	else if (!this->sound_1_music_0)
	{
		this->music.stop();
	}
}

/*Update Functions*/
void Audio::updateFadeIn()
{
	if (this->fadeIn)
	{
		if (this->volumeCounter <= 100.f)
		{
			this->volumeCounter += 0.5f;
			//std::cout << "Volume Counter FADE IN: " << this->volumeCounter << '\n';
			this->setVolume(this->volumeCounter);
		}
		else if (this->volumeCounter >= 100.f)
		{
			std::cout << "DONE Fading In!" << '\n';
			//this->volumeCounter == 100.f;
			this->fadeIn = false;
		}
	}
}
void Audio::updateFadeOut()
{
	if (this->fadeOut)
	{
		if (this->volumeCounter > 0.f)
		{
			this->volumeCounter -= 0.5f;
			//std::cout << "Volume Counter FADE OUT: " << this->volumeCounter << '\n';
			this->setVolume(this->volumeCounter);
		}
		else if (this->volumeCounter <= 0.f)
		{
			this->volumeCounter = 0.f; 

			if (this->sound_1_music_0)
			{
				this->sound.stop();
				std::cout << "DONE Fading Out!" << '\n';
				//std::cout << "Volume Counter: " << this->volumeCounter << '\n';
				this->fadeOut = false;
			}
			else if (!this->sound_1_music_0)
			{
				this->music.stop();
				std::cout << "DONE Fading Out!" << '\n';
				//std::cout << "Volume Counter: " << this->volumeCounter << '\n';
				this->fadeOut = false;
			}
		}
	}
}
void Audio::update()
{
	this->updateFadeIn();
	this->updateFadeOut();
}
