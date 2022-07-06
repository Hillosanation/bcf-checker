# bcf-checker
Checks whether setups are the best possible ones in a given sequence of queues. A succcessor of the oqb tree-searching code.

# Dependancies
* sfinder-fixed-180.jar (jstris 180)

* node
* glueFumen.js (included)

# Usage
## Generate target sequences

While in sfinder's directory, generate the sequences you want the bcf of, using ``util fig``, and pipe the output to a file. 

Example: ```java -jar sfinder.jar util seq -hh yes -p 'SS,[LS]!,[TIOJZ]!,*p2' > 'sequence.txt'``` (Powershell)

It is safe to only keep one of two sequences if they differ by only the first two pieces. (``\'SZ,[LS]!,[TIOJZ]!,\*p2\'`` and ``\'[SZ]!,[LS]!,[TIOJZ]!,\*p2\'`` should yield the same results.)

Paste the file into the directory ``bcf-checker.py`` is in.

## Configure settings in ``bcf-checker.py``

Look for the following variables in ``Settings/config.txt``.

``\_numSetupPieces`` - The number of pieces considered to be used in the setup (Ex: ``4``)

``\_recurseDepth`` - The number of pieces that will be placed in total (Ex: ``4``)

``SolveThresholdPercentage`` - Minimum solve chace chance the setup should have (between 0 and 1). The lower the minimum percent is, the more branches will the explored, the longer it will take. (Ex: ``0.7595``)

``SFinderDir`` - Paste in the directory of where your sfinder directory is. (Ex: nice try)

``SequenceFile`` - File name of the sequence file containing the generated sequences. (Ex: ``sequence.txt``)

Save the file and start running to begin searching for the bcf.

## Extracting setups
### Extracting setups from console output

You could pipe the output from the command line to a file like so:

```bcf-picker.exe > 'output.txt'``` (Powershell)

you could use this regex: ``(v115@.+)`` to find the relavent setups from the console output.

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
