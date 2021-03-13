#include "MeshLoading.h"

class Model
{
	std::vector<Mesh> meshes;
	std::vector<Textures> textures_loaded;
	string directory;
    Shader_Object* shader = 0;

public:
    Shader_Object* GetShader() { return shader; }

    Model(std::string Directory, std::string FileName)
    {
        this->loadModel(Directory, FileName);
        SHADER_SOURCE_FILES* shader_file = new SHADER_SOURCE_FILES();
        this->shader = new Shader_Object(shader_file->vertex_source, shader_file->fragment_source);
        this->shader->compile_shaders();
    }

    void Draw(Transformations* transform)
    {
        glUseProgram(this->shader->get_shader_program());

        int mvp_loc = glGetUniformLocation(this->shader->get_shader_program(), "MVP");
        glUniformMatrix4fv(mvp_loc, 1, GL_FALSE, glm::value_ptr(transform->Project_On_Screen()));
        int model_loc = glGetUniformLocation(this->shader->get_shader_program(), "model");
        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(transform->Get_Model_Matrix()));
        int viewpos_loc = glGetUniformLocation(this->shader->get_shader_program(), "viewpos");
        glUniformMatrix4fv(viewpos_loc, 1, GL_FALSE, glm::value_ptr(EngineCamera->GetWorldPosition()));

        for (GLuint i = 0; i < this->meshes.size(); i++)
        {
            this->meshes[i].Draw(this->shader);
        }
        glUseProgram(0);
    }

	void ProcessNode(aiNode* node, const aiScene* scene)
	{
		for (GLuint i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			this->meshes.push_back(this->ProcessMesh(mesh, scene));
		}

		for (GLuint i = 0; i < node->mNumChildren; i++)
		{
			this->ProcessNode(node->mChildren[i], scene);
		}
	}

    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> vertices;
        vector<GLuint> indices;
        vector<Textures> textures;

        for (GLuint i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // Positions
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.position = vector;

            // Normals
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;

            // Texture Coordinates
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.texcoord = vec;
            }
            else
            {
                vertex.texcoord = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (GLuint i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            // Retrieve all indices of the face and store them in the indices vector
            for (GLuint j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Process materials
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

            // 1. Diffuse maps
            vector<Textures> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            // 2. Specular maps
            vector<Textures> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    vector<Textures>loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<Textures> textures;
        for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);

            std::cout << str.C_Str() << endl;

            GLboolean skip = false;

            for (GLuint j = 0; j < textures_loaded.size(); j++)
            {
                if (textures_loaded[j].path == str)
                {
                    textures.push_back(textures_loaded[j]);
                    skip = true;

                    break;
                }
            }

            if (!skip)
            {
                Textures texture;
                texture.Texture_ID = texture.Load_Texture(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str;
                textures.push_back(texture);

                this->textures_loaded.push_back(texture);
            }
        }

        return textures;
    }

private:
    void loadModel(std::string Directory, std::string FileName)
    {
        Assimp::Importer importer;
        this->directory = Directory;
        std::cout << Directory + FileName << endl;
        const aiScene* scene = importer.ReadFile((Directory + FileName).c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
            return;
        }
       
        this->ProcessNode(scene->mRootNode, scene);
    }
};