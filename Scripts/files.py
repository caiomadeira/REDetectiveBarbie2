import os
from collections import Counter

def get_extension_description(extension):
    """Retorna uma breve descrição de uma extensão de arquivo."""
    descriptions = {
        '.bik': 'Arquivo de vídeo codificado. Você pode usar o VLC pra reproduzi-los.',
        '.wpk': 'Arquivo para compactação de outros arquivos. Pode conter gráficos, sons ou outros recursos usados pelo jogo.',
        '.bbw': ' Pode ser um formato proprietário do jogo para armazenar informações, como cenários, posições ou configurações.',
        '.cmp': 'Arquivo compactado ou de paleta de cores.',
        '.gsc': 'Possível Significado: Game Script ou Game Source Code.',
        '.spr': 'Contém gráficos de personagens, objetos ou animações do jogo.',
        '.wad': "Where's All the Data?Arquivo que contém vários recursos do jogo (texturas, mapas, sons, etc.), muito comum em jogos como Doom e Quake."
    } 
    return descriptions.get(extension, '')

def list_extensions_in_directory(root_dir):
    """Lista todas as extensões de arquivos em um diretório e subdiretórios."""
    extensions_counter = Counter()

    for dirpath, dirnames, filenames in os.walk(root_dir):
        for file in filenames:
            _, ext = os.path.splitext(file)
            if ext:
                extensions_counter[ext] += 1

    return extensions_counter

def main():
    # Diretório inicial
    root_dir = r"C:\Users\caiom\OneDrive\Área de Trabalho\PC_RE\BarbieDetective2Extracted"

    if not os.path.exists(root_dir):
        print("O diretório especificado não existe.")
        return

    # Obter as extensões e suas contagens
    extensions_counter = list_extensions_in_directory(root_dir)

    print("\nExtensões encontradas e descrições:")
    for ext, count in extensions_counter.most_common():
        description = get_extension_description(ext)
        print(f"Extensão: {ext}, Descrição: {description}, Quantidade: {count}")

if __name__ == "__main__":
    main()
