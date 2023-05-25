
class MusicAnarchy{
  private:
    Music music;
  public:
    void init_music(std::string filename);
    void set_position(int length);
    void play_music();
    float get_current_timestamp();
};
