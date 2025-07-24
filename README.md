# Ray Tracing Project

Este é um projeto de ray tracing implementado em C++ que gera imagens renderizadas de esferas com diferentes materiais (Lambertiano e Metal).

## Estrutura do Projeto

```
main/
├── dependence/          # Headers do projeto
│   ├── camera.h
│   ├── hitable_list.h
│   ├── hitable.h
│   ├── lambertian.h
│   ├── material.h
│   ├── metal.h
│   ├── ray.h
│   ├── sphere.h
│   └── vec3.h
├── src/                 # Código fonte
│   ├── scene.cpp        # Versão sequencial
│   ├── scene_parallel.cpp # Versão paralela (OpenMP)
│   └── output/          # Pasta de saída das imagens
└── tests/               # Arquivos de teste
```

## Ferramentas Necessárias

### 1. Compilador C++

- **MinGW-w64** ou **Visual Studio Build Tools**
- Deve suportar C++11 ou superior
- Para versão paralela: suporte a OpenMP

### 2. ImageMagick (para conversão PPM → PNG)

- **Windows**: `winget install ImageMagick.ImageMagick`
- **Linux**: `sudo apt install imagemagick`
- **macOS**: `brew install imagemagick`

## Como Testar o Projeto

### 1. Compilar o Código

Navegue até a pasta `main/src/`:

```bash
cd main/src
```

**Versão Sequencial:**

```bash
g++ -I.. scene.cpp -o scene
```

**Versão Paralela (OpenMP):**

```bash
g++ -fopenmp -I.. scene_parallel.cpp -o scene_parallel
```

### 2. Executar o Programa

**Windows:**

```bash
.\scene.exe
```

**Linux/macOS:**

```bash
./scene
```

### 3. Converter PPM para PNG

Após a execução, o programa gerará um arquivo `scene.ppm` na pasta `output/`. Para converter para PNG:

```bash
magick output/scene.ppm output/scene.png
```

**Ou usando o comando convert (versões antigas do ImageMagick):**

```bash
convert output/scene.ppm output/scene.png
```

## Parâmetros Configuráveis

No arquivo `scene.cpp`, você pode ajustar:

- `nx`: Largura da imagem (default: 700)
- `ny`: Altura da imagem (default: 400)
- `ns`: Número de amostras por pixel (default: 500)

## Resultado Esperado

O programa renderiza uma cena com:

- 3 esferas com diferentes materiais
- Fundo gradiente azul-branco
- Anti-aliasing através de multiple sampling
- Correção gamma aplicada

**Tempo de execução:** Varia conforme configuração (alguns segundos a minutos)

## Troubleshooting

1. **Erro de compilação "No such file or directory":**

   - Verifique se está na pasta `main/src/`
   - Use `-I..` para incluir os headers da pasta `dependence`

2. **ImageMagick não encontrado:**

   - Instale com `winget install ImageMagick.ImageMagick`
   - Reinicie o terminal após instalação

3. **Arquivo PPM não abre:**
   - Use um visualizador que suporte PPM (GIMP, IrfanView)
   - Ou converta para PNG usando ImageMagick
