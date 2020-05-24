
   typedef struct Profile Profile;//creation d'un type de variable profil qui contiendra toute les info de configuration
	struct Profile
	{
		int mode;
		int lang;
		char prompt[32];
	};




	void wconfig();//fonction qui nous permet d'editer la configuration du shell

	int rconfigp();//fonction qui configure le prompt et qui verifie que la configuration a était faite


