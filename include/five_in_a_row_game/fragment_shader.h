#ifndef FIVE_IN_A_ROW_GAME_FRAGMENT_SHADER_H
#define FIVE_IN_A_ROW_GAME_FRAGMENT_SHADER_H

class ShaderProgram;

class FragmentShader {
 public:
  FragmentShader(const char * source);
  FragmentShader(int _placeholder, const char * file_name);
  FragmentShader(FragmentShader &&) = default;
  FragmentShader(const FragmentShader &) = default;
  FragmentShader & operator=(FragmentShader &&) = default;
  FragmentShader & operator=(const FragmentShader &) = default;
  ~FragmentShader();

  void AttachTo(const ShaderProgram & shader_program) const;
  void DetachFrom(const ShaderProgram & shader_program) const;

 private:
  void CheckErrors() const;

 private:
  unsigned id_;
};

#endif  // FIVE_IN_A_ROW_GAME_FRAGMENT_SHADER_H
