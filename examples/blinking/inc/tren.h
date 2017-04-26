// CABECERA DE TREN

static int state = 0;//guarda el estado actual de la maquina

void check_state()
{
switch(state)
{
	// <---Estado Verde Inicial 000
	case 0:
	if (input_key(4))
	{
		state = 4; // Amarillo Normal 100
	}
	else if (input_key(0))
	{
		state = 0; // Mantiene estado 000
	}
	else 
	{
		state = 5;// Estado de Error
	}
	break;
	//Estado Rojo Final
	case 1:
	if (input_key(0))
	{
		state = 0;
	}
	else if (input_key(1))
	{
		state = 1;
	}
	else
	{
		state = 5;
	}
	break;

	case 2:
	if (input_key(0))
	{
		state = 9;
	}
	else if (input_key(3))
	{
		state = 3;
	}
	else if (input_key(2))
	{
		state = 2;
	}
	else
	{
		state = 5;
	}
	break;

	case 3:
	if (input_key(1))
	{
		state = 1;
	}
	else if (input_key(3))
	{
		state = 3;
	}
	else
	{
		state = 5;
	}
	break;

	case 4:
	if (input_key(6))
	{
		state = 6;
	}
	else if (input_key(0))
	{
		state = 8;
	}
	else if (input_key(4))
	{
		state = 4;
	}
	else
	{
		state = 5;
	}

	break;

	case 5:
	//ESTADO DE ERROR NO SE PUEDE SALIR NEVER
	//INFINITE LOOP PLEASE RESTAR 
	break;
	case 6:
	if (input_key(7))
	{
		state = 7;
	}
	else if (input_key(2))
	{
		state = 2;
	}
	else if (input_key(6))
	{
		state = 6;
	}
	else
	{
		state = 5;
	}
	break;

	case 7:
	if (input_key(3))
	{
		state = 3;
	}
	else if (input_key(7))
	{
		state = 7;
	}
	else
	{
		state = 5;
	}
	break;

	case 8:
	if (input_key(2))
	{
		state = 2;
	}
	else if (input_key(0))
	{
		state = 8;
	}
	else
	{
		state = 5;
	}
	break;
	case 9:
	if (input_key(1))
	{
		state = 1;
	}
	else if (input_key(0))
	{
		state = 9;
	}
	else
	{
		state = 5;
	}
	break;
}

} 




