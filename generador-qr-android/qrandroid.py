import qrcode



def crear_qr_link (link: str, name: str = 'imagen'):
    img = qrcode.make(link)
    img.save(name + '.png')


cadena = input("Ingresa la cadena o link ")

nombre_qr = input("Ingresa el nombre del archivo imagen ")


crear_qr_link(cadena, nombre_qr)