dia_inicial = int(input().split()[1])
horario_inicial = [int(i) for i in input().split(':')]
hora_inicial = horario_inicial[0]
minuto_inicial = horario_inicial[1]
segundo_inicial = horario_inicial[2]

dia_final = int(input().split()[1])
horario_final = [int(i) for i in input().split(':')]
hora_final = horario_final[0]
minuto_final = horario_final[1]
segundo_final = horario_final[2]

dias = dia_final - dia_inicial;

total_segundos_inicial = hora_inicial * 60 * 60 + minuto_inicial * 60 + segundo_inicial
total_segundos_final = hora_final * 60 * 60 + minuto_final * 60 + segundo_final

if total_segundos_inicial > total_segundos_final:
    total_segundos = 24 * 60 * 60 - total_segundos_inicial + total_segundos_final
    dias -= 1
else:
    total_segundos = total_segundos_final - total_segundos_inicial

horas = int(total_segundos / (60 * 60))
total_segundos -= (horas * 60 * 60)
minutos = int(total_segundos / (60))
total_segundos -= (minutos * 60)
segundos = total_segundos

print("{} dia(s)".format(dias))
print("{} hora(s)".format(horas))
print("{} minuto(s)".format(minutos))
print("{} segundo(s)".format(segundos))
