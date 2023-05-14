#ifndef FIVE_IN_A_ROW_G_TEXTURE_H_
#define FIVE_IN_A_ROW_G_TEXTURE_H_

class Texture2D {
 public:
  Texture2D(const char * file_name);
  void Bind(const unsigned which) const;

 private:
  unsigned texture_id_;
};

#endif
