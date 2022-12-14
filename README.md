# bcf-checker (best-chance-field checker)
Checks whether setups are the best possible ones in a given sequence of queues. A successor of the oqb tree-searching code.

# Dependencies
* [sfinder](https://github.com/knewjade/solution-finder/releases/) v1.40+
* jstris180.properties by metallicLurker (included in /kicks/)

* glueFumen.js (modified from [Marfung37/GluingFumens](https://github.com/Marfung37/GluingFumens), included)
* [node.js](https://nodejs.org/en/) for glueFumen
* [yargs](https://yargs.js.org/) for glueFumen
* [tetris-fumen](https://github.com/knewjade/tetris-fumen) for glueFumen
* [npm](https://docs.npmjs.com/downloading-and-installing-node-js-and-npm) for installing yargs and tetris-fumen

* [p-ranav/argparse](https://github.com/p-ranav/argparse) (for copmilation only, included)

# Usage

## Generate target sequences

While in sfinder's directory, generate the sequences you want the BCF of, using ``util fig``, and pipe the output to a file. 

Example: ```java -jar sfinder.jar util seq -hh yes -p 'SS,[LS]!,[TIOJZ]!,*p2' > 'sequence.txt'``` (Powershell)

It is safe to only keep one of two sequences if they differ by only the first two pieces. (``'SZ,[LS]!,[TIOJZ]!,*p2'`` and ``'[SZ]!,[LS]!,[TIOJZ]!,*p2'`` should yield the same results.)

Paste the file into the directory ``bcf-checker.py`` is in.

## Add arguments in the command line

Required:

* ``-vis`` (``-visible-pieces``) - The number of pieces that are taken into account before placing any pieces. (Ex: ``4``)

* ``-pp`` (``--placed-pieces``) - The total number of pieces placed in the setup. (Currently cannot exceed 4.) (Ex: ``4``)

* ``-sfp`` (``--sfinder-path``) - The path of ``sfinder.jar``.

* ``-op`` (``--output-path``) - The path to the location of the output file. (Ex: ``output/congruent_output_SS-LS.txt``)

Optional:

* ``-inc`` (``--increased-vision``) - The number of pieces that are taken into account additionally after placing each piece. (This should be set to 0 for BCF purposes.)

* ``-tsp`` (``--tree-succeed-percentage``) - The minimum percentage of trees that must be successful to keep the parent tree node.

* ``-sp`` (``--sequence-path``) - The path to the ``sequence.txt`` file generated in the previous step. (Ex: ``input/sequence.txt``)

* ``-sm`` (``--skip-mirror``) - Whether the mirrored field will be searched or not. (Ex: ``1``)

``SkipCongruent`` (soon)

Example command: ``& ./bcf-checker.exe @('-vis', '4', '-inc', '0', '-pp', '4', '-sfp', <sfinder-path>, '-op', 'output/congruent_output_SS-LS.txt')`` (powershell)

## Set percentages in ``input/Best_Percentages.txt``

Set the best known percentage for the specific queue in CSV format. You only need to specify queues up to ``--visible-pieces``.

Ex:
```
SSLS,0.7595
SSSL,0.7595
```

Save the files and start running the .exe file to begin searching for the BCF.

## Extracting setups

### Extracting setups from the console output (Not recommended)

You could pipe the output from the command line to a file like so:

```& ./bcf-checker.exe ... > 'output.txt'``` (Powershell)

you could use this regex: ``(v115@.+)`` to extract the relevant setups from the console output.

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
