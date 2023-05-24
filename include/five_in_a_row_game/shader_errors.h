#ifndef FIVE_IN_A_ROW_GAME_SHADER_ERRORS_H_
#define FIVE_IN_A_ROW_GAME_SHADER_ERRORS_H_

class ShaderError {};
class ShaderCompilationError : public ShaderError {};
class ShaderLinkingError : public ShaderError {};

#endif  //! FIVE_IN_A_ROW_GAME_SHADER_ERRORS_H_
