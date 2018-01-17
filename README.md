# A Fast Bit-Vector Algorithm for Approximate String Matching Based on Dynamic Programming
This repository is implementation of Gene Myers [algorithm](https://dl.acm.org/citation.cfm?id=316550) for approximate string matching which runs in `O(kn/w)` time.

## Building
After cloning this repository just execute `make` in command line which will generate `agrep` executable.

## Usage
`agrep` searches for minimal edit distance between pattern and input text and prints all (end) positions (0-based) in input text where pattern matches input text with minimal edit distance.

Output example:
```
k=2
14
84
85
95
```
`k=2` is minimal edit distance between pattern and input text followed by all positions (0-based) where pattern matches input text with edit distance 2.

`agrep [pattern] [k] [input_file] [output_file]` <br>

`pattern` - pattern used to match against input text. Mandatory argument. <br>
`k` - minimal edit distance to search for. If `k=-1` minimal edit distance will be set to pattern length. Mandatory argument. <br>
`input_file` - path to file with input text. Mandatory argument. <br>
`output_file` - path to file where agrep should write its output. If `output_file` is not provided output will be printed on standard output. Optional argument. <br>

Example usage:

data/example.txt
```
ACTGA
```

`agrep TC -1 test_data/example.txt` <br>

Output: <br>
```
k=1
1
2
3
```

## License
[MIT License](LICENSE) <br>
Copyright &copy; 2017.
Martin Gluhak, Luka Dulčić and Mihael Nikić


Project for [Bioinformatics course](https://www.fer.unizg.hr/en/course/bio) at FER, Zagreb 2017./2018.
