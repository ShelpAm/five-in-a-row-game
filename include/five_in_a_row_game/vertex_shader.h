#ifndef FIVE_IN_A_ROW_GAME_VERTEX_SHADER_H
#define FIVE_IN_A_ROW_GAME_VERTEX_SHADER_H

class ShaderProgram;

class VertexShader {
 public:
  VertexShader(const char * source);
  VertexShader(int _placeholder, const char * file_name);
  VertexShader(VertexShader &&) = default;
  VertexShader(const VertexShader &) = default;
  VertexShader & operator=(VertexShader &&) = default;
  VertexShader & operator=(const VertexShader &) = default;
  ~VertexShader();

  void AttachTo(const ShaderProgram & shader_program) const;
  void DetachFrom(const ShaderProgram & shader_program) const;

 private:
  void CheckErrors() const;

 private:
  unsigned id_;
};

#endif  // FIVE_IN_A_ROW_GAME_VERTEX_SHADER_H
