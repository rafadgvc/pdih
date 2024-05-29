library(tuneR)
library(seewave)
library(audio)


setwd("C:/Users/Usuario/Desktop/SD/4 II/PDIH/P5")

# cargar archivos de sonido (wav):

pablo <- readWave('pablorienda.wav')
rafa  <- readWave('rafaeldelgado.wav')
fallo <- readWave('fallo.wav')
bd <- readWave('bd.wav')


# mostrar la onda del sonido:

plot( extractWave(pablo, from = 1, to = 393984) )

plot( extractWave(rafa, from = 1, to = 393984) )

plot( extractWave(fallo, from = 1, to = 393984) )

# Mostrar los datos de los sonidos: 
pablo
str(pablo)

rafa
str(rafa)

fallo
str(fallo)

# Mezclar los tres sonidos:
mezcla1 <- pastew(rafa, pablo, output="Wave")
mezcla1

mezcla <- pastew(mezcla1, fallo, output="Wave")
plot( extractWave(mezcla, from = 1, to=265573) )



# Filtrar el sonido nuevo para que elimine frecuencias entre 10000 y 20000 Hz:
filtracion <- fir(
                  wave = mezcla,
                  from = 10000, to = 20000, 
                  bandpass = FALSE,
                  output = "Wave"
                )
plot( extractWave(filtracion, from = 1, to=265573) )


# Guardar audio: 
writeWave(filtracion, file.path("mezcla.wav") )



bd_echo <- echo(bd, amp=c(0.6, 0.3, 0.15, 0.05), delay=c(0.1, 0.2, 0.3, 0.4), output="Wave")

plot( extractWave(bd_echo, from = 1, to=265573) )


# Invertir el sonido
bd_reversed <- rev(bd_echo)

writeWave(bd_reversed, file.path("alreves.wav") )



