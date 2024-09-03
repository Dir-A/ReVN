## Valkyria_SDT_TextEditor
 - export text from `.sdt` to json
 - import text from json to `.sdt`
> Q: ***Can it be longer than the original text?***  
> A: yes, but the maximum text buffer size of this engine is 260 bytes.

## Valkyria_DAT_Editor
 - unpack `.dat`
 - repack `.dat`
> Q: ***How to make a patch?***  
> A: if the original .dat file name is `data06-00.dat`, just pack the files that need to replace as new pack name `data06-01.dat` or `data06-02.dat` etc.

## Valkyria_SDT_Signer
sdt file has a piece of data that is used to verify that the size of the sdt file has been modified.
this tool can be used to sign the resized sdt file.
**SDT_TextEditor** signed by default, so it doesn't need to be signed again.

# More
For more details, please refer to [RxValkyria](https://github.com/ZQF-ReVN/RxValkyria).
