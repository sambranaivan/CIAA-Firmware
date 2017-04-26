// CABECERA DE TREN

int STATE = 0;
int SENSOR = 0;
int LAST_STATE = 0;


void update_STATE()
{
	switch(STATE)
	{
		// <---Estado Verde Inicial 000
		case 0:
		if (SENSOR == 4)
		{
			STATE = 4; // Amarillo Normal 100
		}
		else if (SENSOR == 0)
		{
			STATE = 0; // Mantiene estado 000
		}
		else 
		{
			LAST_STATE = 0;
			STATE = 5;// Estado de Error
		}
		break;
		//Estado Rojo Final
		case 1:
		if (SENSOR == 0)
		{
			STATE = 0;
		}
		else if (SENSOR == 1)
		{
			STATE = 1;
		}
		else
		{
			LAST_STATE = 1;
			STATE = 5;
		}
		break;

		case 2:
		if (SENSOR == 0)
		{
			STATE = 9;
		}
		else if (SENSOR == 3)
		{
			STATE = 3;
		}
		else if (SENSOR == 2)
		{
			STATE = 2;
		}
		else
		{
			LAST_STATE = 2;
			STATE = 5;
		}
		break;

		case 3:
		if (SENSOR == 1)
		{
			STATE = 1;
		}
		else if (SENSOR == 3)
		{
			STATE = 3;
		}
		else
		{
			LAST_STATE = 3;
			STATE = 5;
		}
		break;

		case 4:
		if (SENSOR == 6)
		{
			STATE = 6;
		}
		else if (SENSOR == 0)
		{
			STATE = 8;
		}
		else if (SENSOR == 4)
		{
			STATE = 4;|
		}
		else
		{
			LAST_STATE = 4;
			STATE = 5;
		}

		break;

		case 5:
		//ESTADO DE ERROR NO SE PUEDE SALIR NEVER
		//INFINITE LOOP PLEASE RESTAR 
		break;
		case 6:
		if (SENSOR == 7)
		{
			STATE = 7;
		}
		else if (SENSOR == 2)
		{
			STATE = 2;
		}
		else if (SENSOR == 6)
		{
			STATE = 6;
		}
		else
		{
			LAST_STATE = 6;
			STATE = 5;
		}
		break;

		case 7:
		if (SENSOR == 3)
		{
			STATE = 3;
		}
		else if (SENSOR == 7)
		{
			STATE = 7;
		}
		else
		{
			LAST_STATE = 7;
			STATE = 5;
		}
		break;

		case 8:
		if (SENSOR == 2)
		{
			STATE = 2;
		}
		else if (SENSOR == 0)
		{
			STATE = 8;
		}
		else
		{
			LAST_STATE = 8;
			STATE = 5;
		}
		break;
		case 9:
		if (SENSOR == 1)
		{
			STATE = 1;
		}
		else if (SENSOR == 0)
		{
			STATE = 9;
		}
		else
		{
			LAST_STATE = 9;
			STATE = 5;
		}
		break;
		default: 
		STATE = 10;
	}
}







