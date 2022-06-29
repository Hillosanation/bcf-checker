# bcf-checker
Checks whether setups are the best possible ones in a given sequence of queues. A succcessor of the oqb tree-searching code.

# Dependancies
* sfinder.jar
* tetris-fumen

# Usage
## Generate target sequences

While in sfinder's directory, generate the sequences you want the bcf of, using ``util fig``, and pipe the output to a file. 

Example: ```java -jar sfinder.jar util seq -hh yes -p 'SS,[LS]!,[TIOJZ]!,*p2' > 'sequence.txt'``` (Powershell)

It is safe to only keep one of two sequences if they differ by only the first two pieces. (If fact, this reduces search time.)

Paste the file into the directory the source file of ``congruent-pickerv4.5.py`` is in.

## Configure settings in ``congruent-pickerv4.5.py``

Look for the following variables in ``congruent-pickerv4.5.py``.

``SFinderDir`` - Paste in the directory of where your sfinder directory is. (Ex: nice try)

``SequenceFile`` - File name of the sequence file containing the generated sequences. (Ex: sequence.txt)

``_numSetupPieces`` - The number of pieces considered to be used in the setup (Ex: 4)

``_recurseDepth`` - The number of pieces that will be placed in total (Ex: 4)

``SolveThresholdPercentage`` - Minimum solve chace chance the setup should have (between 0 and 1). The lower the minimum percent is, the more branches will the explored, the longer it will take. (Ex: 0.7595)

(Could I have made the arguments command-line instead of modifying the file? Yes.)

Save the file and start running to begin searching for the bcf.

## Extracting setups
### Extracting setups from console output

You could pipe the output from the command line to a file like so:

```python3 congruent-pickerv4.5.py > 'output.txt'``` (Powershell)

The indexes preceded by ``progress:`` with the appropiate amount of numbers will be the finial setups.

you could use this regex: ``progress: {((?:(\d+)(?:, |})){4})`` (4 according to ``_recurseDepth``) to find which lines are possible setups

Example of a relavent set of indexes: ``progress: {249, 234, 251, 61}, 75.95``

### Extracting setups from file output
Collect all pieces from the layers of a tree to get a set of indexes corresponding to the solve percentage provided in the last layer

Example:
```
249	100.00%
		61	96.19%
				234	79.56%
						251	75.95%
```
means the set of indexes ``{249, 61, 234, 251}`` has a solve chance of ``75.95%``

## Conversion from indexes to fumen

use ``indexes-to-fumen.js`` to convert the set of indexes into a fumen string

Example:  ``node indexes-to-fumen.js X 249 61 234 251`` -> ``v115@/gB8GeB8HeD8DeE8CeC8JeAgH``
