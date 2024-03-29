#include "Shader.h"

// Constructeurs et Destructeur

Shader::Shader() : m_vertexID(0), m_fragmentID(0), m_programID(0), m_vertexSource(), m_fragmentSource()
{
}


Shader::Shader(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader

    charger();
}


Shader::Shader(std::string vertexSource, std::string fragmentSource) : m_vertexID(0), m_fragmentID(0), m_programID(0),
                                                                       m_vertexSource(vertexSource), m_fragmentSource(fragmentSource)
{
}


Shader::~Shader()
{
    // Destruction du shader

    glDeleteShader(m_vertexID);
    glDeleteShader(m_fragmentID);
    glDeleteProgram(m_programID);
}


// M�thodes

Shader& Shader::operator=(Shader const &shaderACopier)
{
    // Copie des fichiers sources

    m_vertexSource = shaderACopier.m_vertexSource;
    m_fragmentSource = shaderACopier.m_fragmentSource;


    // Chargement du nouveau shader

    charger();


    // Retour du pointeur this

    return *this;
}


bool Shader::charger()
{
    // Destruction d'un �ventuel ancien Shader

    if(glIsShader(m_vertexID) == GL_TRUE)
        glDeleteShader(m_vertexID);

    if(glIsShader(m_fragmentID) == GL_TRUE)
        glDeleteShader(m_fragmentID);

    if(glIsProgram(m_programID) == GL_TRUE)
        glDeleteProgram(m_programID);


    // Compilation des shaders

    if(!compilerShader(m_vertexID, GL_VERTEX_SHADER, m_vertexSource))
        return false;

    if(!compilerShader(m_fragmentID, GL_FRAGMENT_SHADER, m_fragmentSource))
        return false;


    // Cr�ation du programme

    m_programID = glCreateProgram();


    // Association des shaders

    glAttachShader(m_programID, m_vertexID);
    glAttachShader(m_programID, m_fragmentID);


    // Verrouillage des entr�es shader

    glBindAttribLocation(m_programID, 0, "in_Vertex");
    glBindAttribLocation(m_programID, 1, "in_Color");
    glBindAttribLocation(m_programID, 2, "in_TexCoord0");


    // Linkage du programme

    glLinkProgram(m_programID);


    // V�rification du linkage

    GLint erreurLink(0);
    glGetProgramiv(m_programID, GL_LINK_STATUS, &erreurLink);


    // S'il y a eu une erreur

    if(erreurLink != GL_TRUE)
    {
        // R�cup�ration de la taille de l'erreur

        GLint tailleErreur(0);
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de m�moire

        char *erreur = new char[tailleErreur + 1];


        // R�cup�ration de l'erreur

        glGetShaderInfoLog(m_programID, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        std::cout << erreur << std::endl;


        // Lib�ration de la m�moire et retour du bool�en false

        delete[] erreur;
        glDeleteProgram(m_programID);

        return false;
    }



    // Sinon c'est que tout s'est bien pass�

    else
        return true;
}


bool Shader::compilerShader(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Cr�ation du shader

    shader = glCreateShader(type);


    // V�rification du shader

    if(shader == 0)
    {
        std::cout << "Erreur, le type de shader (" << type << ") n'existe pas" << std::endl;
        return false;
    }


    // Flux de lecture

    std::ifstream fichier(fichierSource.c_str());


    // Test d'ouverture

    if(!fichier)
    {
        std::cout << "Erreur le fichier " << fichierSource << " est introuvable" << std::endl;
        glDeleteShader(shader);

        return false;
    }


    // Strings permettant de lire le code source

    std::string ligne;
    std::string codeSource;


    // Lecture

    while(getline(fichier, ligne))
        codeSource += ligne + '\n';


    // Fermeture du fichier

    fichier.close();


    // R�cup�ration de la chaine C du code source

    const GLchar* chaineCodeSource = codeSource.c_str();


    // Envoi du code source au shader

    glShaderSource(shader, 1, &chaineCodeSource, 0);


    // Compilation du shader

    glCompileShader(shader);


    // V�rification de la compilation

    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);


    // S'il y a eu une erreur

    if(erreurCompilation != GL_TRUE)
    {
        // R�cup�ration de la taille de l'erreur

        GLint tailleErreur(0);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &tailleErreur);


        // Allocation de m�moire

        char *erreur = new char[tailleErreur + 1];


        // R�cup�ration de l'erreur

        glGetShaderInfoLog(shader, tailleErreur, &tailleErreur, erreur);
        erreur[tailleErreur] = '\0';


        // Affichage de l'erreur

        std::cout << erreur << std::endl;


        // Lib�ration de la m�moire et retour du bool�en false

        delete[] erreur;
        glDeleteShader(shader);

        return false;
    }


    // Sinon c'est que tout s'est bien pass�

    else
        return true;
}


// Getter

GLuint Shader::getProgramID() const
{
    return m_programID;
}

GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	}
	else
	{
		std::cout << "Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !" << vertex_file_path << std::endl;
		getchar();
		return 0;
	}

	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	std::cout << "Compiling shader : " << vertex_file_path << std::endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << VertexShaderErrorMessage[0] << std::endl;
	}



	// Compile Fragment Shader
	std::cout << "Compiling shader : " << fragment_file_path << std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << FragmentShaderErrorMessage[0] << std::endl;
	}

	std::cout << "Linking program\n" << std::endl;
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 )
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << ProgramErrorMessage[0] << std::endl;
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
