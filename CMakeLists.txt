cmake_minimum_required(VERSION 3.12)
project(project VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} /usr/local/include)
link_directories(/usr/local/lib)

add_executable(project 
	glad.cxx 
	stb_image.cxx 
	obj_loader.cxx 
	display.cxx
	shader.cxx 
	mesh.cxx 
	model.cxx 
	texture.cxx 
	main.cxx 
)

target_link_libraries(project
	${OPENGL_LIBRARIES}
	glfw
	dl
	assimp
)