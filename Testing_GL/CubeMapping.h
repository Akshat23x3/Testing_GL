class CubeMapping
{
	GLuint VAO = 0, VBO = 0;
	Shader_Object* shader = 0;
    Textures* texture = 0;

    void Initiate_Shader(const string file_path)
    {
        this->shader->compile_shaders();
        GLfloat vertices[] = {
            // Positions
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glBindVertexArray(0);

        std::vector<const GLchar*> faces;
        faces.push_back("Data/Skyboxes/right.tga");
        faces.push_back("Data/Skyboxes/left.tga");
        faces.push_back("Data/Skyboxes/top.tga");
        faces.push_back("Data/Skyboxes/bottom.tga");
        faces.push_back("Data/Skyboxes/back.tga");
        faces.push_back("Data/Skyboxes/front.tga");

        this->texture->Load_CubeMapTexture(faces);
    }

public:
	CubeMapping(const string file_path)
	{
        SHADER_SOURCE_FILES* shader_file = new SHADER_SOURCE_FILES();
		this->shader = new Shader_Object(shader_file->cubemapping_vs, shader_file->cubemapping_fs);
        texture = new Textures();
        delete shader_file;
        this->Initiate_Shader(file_path);
	}

    void Render(Transformations* transform)
    {
        glm::mat4 view = glm::mat4(glm::mat3(EngineCamera->GetViewMatrix()));
        glDepthFunc(GL_LEQUAL);
        glUseProgram(this->shader->get_shader_program());
        glUniformMatrix4fv(glGetUniformLocation(this->shader->get_shader_program(), "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(this->shader->get_shader_program(), "projection"), 1, GL_FALSE, glm::value_ptr(transform->Get_Projection_Matrix()));

        glBindVertexArray(this->VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureID());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);
    }
};