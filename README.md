# bcf-checker (best-chance-field checker)
Checks whether setups are the best possible ones in a given sequence of queues. A succcessor of the oqb tree-searching code.

# dependencies
* sfinder-fixed-180.jar (jstris 180)

* [node.js](https://nodejs.org/en/)
* glueFumen.js (included)

# Usage
## Generate target sequences

While in sfinder's directory, generate the sequences you want the BCF of, using ``util fig``, and pipe the output to a file. 

Example: ```java -jar sfinder.jar util seq -hh yes -p 'SS,[LS]!,[TIOJZ]!,*p2' > 'sequence.txt'``` (Powershell)

It is safe to only keep one of two sequences if they differ by only the first two pieces. (``'SZ,[LS]!,[TIOJZ]!,*p2'`` and ``'[SZ]!,[LS]!,[TIOJZ]!,*p2'`` should yield the same results.)

Paste the file into the directory ``bcf-checker.py`` is in.

## Configure settings in ``config.txt``

Look for the following variables in ``Settings/config.txt``.

``_numSetupPieces`` - The number of pieces considered to be used in the setup (Ex: ``4``)

``_recurseDepth`` - The number of pieces that will be placed in total (Ex: ``4``)

``SFinderDir`` - Paste in the directory where your sfinder directory is. (Ex: nice try)

``SequenceFile`` - File path of the sequence file containing the generated sequences. (Ex: ``input/sequence.txt``)

``OutputFile`` - File path of the output file. (Ex: ``output/congruent_output_SS-LS.txt``)

``SkipMirror`` - Does not try piece sequences with explored mirrored setups(boolean). (Ex: ``1``)

``SkipCongruent`` (soon)

## Set percentages in ``Best_Percentages.txt``

Set the best known percentage for the specific queue in csv format. You only need to specify queues up to ``_numSetupPieces + _numEqualPieces``.

Ex:
```
SSLS,0.7595
SSSL,0.7595
```

Save the files and start running the .exe file to begin searching for the BCF.

## Extracting setups

### Extracting setups from console output

You could pipe the output from the command line to a file like so:

```bcf-checker.exe > 'output.txt'``` (Powershell)

you could use this regex: ``(v115@.+)`` to find the relevant setups from the console output.

### Extracting setups from file output
Collect all pieces from the layers of a tree to get a set of indexes corresponding to the solve percentage provided in the last layer

Example:
```
254	100.00%
	138	98.67%
		252	86.71%
			363	80.00%: v115@BhBtIeBtCeg0CeT4Bei0T4MeAgH
```
means the set of indexes ``{254, 138, 252, 363}``, representing the fumen ``v115@BhBtIeBtCeg0CeT4Bei0T4MeAgH`` has a solve chance of ``80.00%``
