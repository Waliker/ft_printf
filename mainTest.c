#include <stdio.h>
#include <wchar.h>
#include "libftprintf.h"
#include <inttypes.h>
#include <locale.h>

void	ft_test2(int *a)
{
	(*a)++;
}

void	ft_test(int *a)
{
	*a = 1;
	printf("valeur de b:%d\n", *a);
	ft_test2(a);
	printf("valeur de b:%d", *a);
}

int		main()
{
	int	b;
	short int shortint = 450;
	char	c;
	unsigned int	ua;

	wchar_t *p = L"je suis été à";
	wint_t	wi = 0x1234;


	setlocale (LC_ALL, "");

/*	b = 3;
	printf(" valeur de b:%d\n", b);
	ft_test(&b);
	printf("valeur de b:%d\n", b);
	printf("LES CAS DE : %%d\n");
	printf("1. Les flags :\n");
	printf("Le flag - & 0 : %02d-\n", 1);
	printf("Multiple flag - et precision :%+02d-\n", 2);
	printf("Flags - & # : %+0d-\n", 3);
	printf("Flags - & + : %----+---2.0d-\n", 4);
	printf("test espace & 0 :% 2d\n", 10);


	ft_printf("Debut des tests :\n");
	ft_printf("Je cherche a afficher un nombre %d\n", 15);
	ft_printf("Je chercher a afficher plusieurs nombres : %d, puis %d\n", 5, 1564);
	ft_printf("Bonjour je m'appelle %s j'ai %d ans\n", "Nelson", 25);
	ft_printf("Voici des tests plus difficiles : un unsigned %u\nun pourcent %%\nun char %c\n", -154, 'd');*/
	ft_printf("Je cherche a afficher un nombre %0-10d-\n", 15);
//	printf("Je cherche a afficher un nombre %0-10d-\n", 15);
	b = ft_printf("Flags - & + : %+5.0d-\n", -0);
//	printf("Valeur de b: %d\n", b);
	b = printf("Flags - & + : %+5.0d-\n", -0);
	printf("Valeur de b: %d\n", b);
	ft_printf("ft Test + grand qu'un int : %d, et un autre %lld\n", INT_MAX + 15, LLONG_MAX);
	printf("Test + grand qu'un int : %d, et un autre %lld\n", INT_MAX + 15, LLONG_MAX);
	printf("Test + grand qu'un int : %s-\n", "coucou");
	ft_printf("LES CONVERTEURS : \n");
	ft_printf("Converteur h : %hd\n", shortint);
	printf("Converteur h : %hd\n", shortint);
	ft_printf("converteur hh : %hhd\n", 300);
	printf("converteur hh : %hhd\n", 300);
	printf("Hexa unsigned :%lx, unsigned :%u\n", 2147483648, INT_MIN);
	printf("%                qw", "cava?", 6);
	ft_printf("%zd\n", 4294967295);
	printf("%zd\n", 4294967295);
	ua = 4;
	printf("Unsigned int test :%+05u\n", ua);
	printf("%hU\n", 4294967296);
	printf("\nTest string:\n");
	printf("%+s\n%0s\n%3.2s\n%-3.2s-\n", "coucou1", "coucou2", "coucou3", "coucou");

	ft_printf("ft_printf\n%+s\n%0s\n%3.2s\n%-3.2s-\n", "coucou1", "coucou2", "coucou3", "coucou");
//	printf("%s\n", ft_itoa_base(INT_MAX, 10));
	printf("%s\n", ft_litoa(LONG_MIN));
	printf("%X, %o, %u\n", 0, 0, 0);
	ft_printf("%X, %o, %u\n", 0, 0, 0);
	ft_printf("%5.2x\n", 5427);
	printf("%5.2x\n", 5427);
	ft_printf(":%5.2d\n", -542);
	printf(":%5.0d\n", -542);
	ft_printf(":% 10.5d\n", -4242);
	printf(":% 10.5d\n", -4242);
	printf("%hhO, %hhO\n", 0, USHRT_MAX);
	ft_printf("%hhO, %hhO\n", 0, USHRT_MAX);
	printf("%d\n", 10 + 0x7f);
	ft_printf("char :%c\n", 48);
	ft_printf("wide char : %C\n", wi);
	printf("test :%4lc-\n", wi);
	ft_printf("test :%4lc-\n", wi);
	printf("test :%-4lc-\n", wi);
	ft_printf("test :%-4lc-\n", wi);
	printf("test char :%2.c\n", 48);
	ft_printf("test char :%2.c\n", 48);
	printf("test char :%-2.c-\n", 48);

	printf("test char :%C\n", 99);
	ft_printf("test char :%C\n", 99);
	ft_printf("test char :%-2.c-\n", 48);
	printf("coucou : %08s\n", "coucou");
	printf("%#10x\n", 100);
	printf("%x\n", 0x004);
	printf("%4.s\n", "42");
	ft_printf("%4.s\n", "42");
	printf("%4.0s\n", "42");

	return (0);
}