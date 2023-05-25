#include "space.hpp"
#include "music.hpp"

void MusicAnarchy::init_music(std::string filename) {
	InitAudioDevice();
	music = LoadMusicStream(filename.c_str());
	PlayMusicStream(music);
}
void MusicAnarchy::set_position(int length){
	SeekMusicStream(music, length);
}
void MusicAnarchy::play_music(){
	UpdateMusicStream(music);
}
float MusicAnarchy::get_current_timestamp(){
	return GetMusicTimePlayed(music);
}
