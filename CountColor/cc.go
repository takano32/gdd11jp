// vim: set noet sts=4 sw=4 ts=4 fdm=marker ft=go :
package main

import (
		"fmt"
		"io"
		"strings"
		/* add more */
		"image/png"
		"container/vector"
)

func CountColor(pngR io.Reader) int {
	/* modify here */
	uniq := new (vector.IntVector)
	// rVector := new (vector.IntVector)
	im, _ := png.Decode(pngR)
	for y := 0; y < im.Bounds().Dy(); y++ {
		for x := 0; x < im.Bounds().Dx(); x++ {
			color := im.At(x, y)
			unique := true
			R, G, B, _ := color.RGBA()
			C := R * 0x10000 + G * 0x100 + B
			c := 0
			for i := 0; i < uniq.Len(); i++ {
				// r, g, b, _ := uniq.At(i).RGBA()
				r := uniq.At(i) / 0x10000
				g := (uniq.At(i) % 0x10000) / 0x100
				b := uniq.At(i) % 0x100
				c = r * 0x10000 + g * 0x100 + b
				fmt.Println(R)
				if uint32(c) == C {
					unique = false
				}
			}
			if unique == true {
				uniq.Push(c)
			}
		}
	}
	return uniq.Len()
}


/* これらの関数は提出時に自動挿入されます。 */
func main() {
	png := GetPngBinary()
	cnt := CountColor(png)
	fmt.Println(cnt)
}

func GetPngBinary() io.Reader {
    // img_strの中身は提出するたびに変化します。
    img_str := "\x89PNG\r\n\x1a\n\x00\x00\x00\rIHDR\x00\x00\x00\x18\x00\x00\x00\x08\x08\x06\x00\x00\x00\xe3\xa1?c\x00\x00\x02\xeeiCCPICC Profile\x00\x00x\x01\x85T\xcfk\x13A\x14\xfe6n\xa9\xd0\"\x08Zk\x0e\xb2x\x90\"IY\xabhE\xd46\xfd\x11bk\x0c\xdb\x1f\xb6E\x90d3I\xd6n6\xeb\xee&\xb5\xa5\x88\xe4\xe2\xd1*\xdeE\xed\xa1\x07\xff\x80\x1ez\xf0d/J\x85ZE(\xde\xab(b\xa1\x17-\xf1\xcdnL\xb6\xa5\xea\xc0\xce~\xf3\xde7\xef}ov\xdf\x00\rr\xd24\xf5\x80\x04\xe4\r\xc7R\xa2\x11il|Bj\xfc\x88\x00\x8e\xa2\tA4%U\xdb\xecN$\x06A\x83s\xf9{\xe7\xd8z\x0f\x81[V\xc3{\xfbw\xb2w\xad\x9a\xd2\xb6\x9a\x07\x84\xfd@\xe0G\x9a\xd9*\xb0\xef\x17q\nY\x12\x02\x88<\xdf\xa1)\xc7t\x08\xdf\xe3\xd8\xf2\xec\x8f9Nyx\xc1\xb5\x0f+=\xc4Y\"|@5-\xce\x7fM\xb8S\xcd%\xd3@\x83H8\x94\xf5qR>\x9c\xd7\x8b\x94\xd7\x1d\x07inf\xc6\xc8\x10\xbdO\x90\xa6\xbb\xcc\xee\xabb\xa1\x9cN\xf6\x0e\x90\xbd\x9d\xf4~N\xb3\xde>\xc2!\xc2\x0b\x19\xad?F\xb8\x8d\x9e\xf5\x8c\xd5?\xe2a\xe1\xa4\xe6\xc4\x86=\x1c\x185\xf4\xf8`\x15\xb7\x1a\xa9\xf85\xc2\x14_\x10M'\xa2Tq\xd9.\r\xf1\x98\xae\xfdV\xf2J\x82p\x908\xcada\x80sZHO\xd7Ln\xf8\xba\x87\x05}&\xd7\x13\xaf\xe2wVQ\xe1y\x8f\x13g\xde\xd4\xdd\xefE\xda\x02\xaf0\x0e\x1d\x0c\x1a\x0c\x9a\rHP\x10E\x04a\x98\xb0P@\x86<\x1a14\xb2r?#\xab\x06\x1b\x93{2u$j\xbbtbD\xb1A{6\xdc=\xb7Q\xa4\xdd<\xfe(\"q\x94C\xb5\x08\x92\xfcA\xfe*\xaf\xc9O\xe5y\xf9\xcb\\\xb0\xd8V\xf7\x94\xad\x9b\x9a\xba\xf2\xe0;\xc5\xe5\x99\xb9\x1a\x1e\xd7\xd3\xc8\xe3sM^|\x95\xd4v\x93WG\x96\xacyz\xbc\x9a\xec\x1a?\xecW\x971\xe6\x825\x8f\xc4s\xb0\xfb\xf1-_\x95\xcc\x97)\x8c\x14\xc5\xe3U\xf3\xeaK\x84uZ17\xdf\x9fl\x7f;=\xe2.\xcf.\xb5\xd6s\xad\x89\x8b7V\x9b\x97g\xfdjH\xfb\xee\xaa\xbc\x93\xe6U\xf9O^\xf5\xf1\xfcg\xcd\xc4c\xe2)1&v\x8a\xe7!\x89\x97\xc5.\xf1\x92\xd8K\xab\x0b\xe2`m\xc7\x08\x9d\x95\x86)\xd2m\x91\xfa$\xd5``\x9a\xbc\xf5/]?[x\xbdF\x7f\x0c\xf5Q\x94\x19\xcc\xd2T\x89\xf7\x7f\xc2*d4\x9d\xb9\x0eo\xfa\x8f\xdb\xc7\xfc\x17\xe4\xf7\x8a\xe7\x9f(\x02/l\xe0\xc8\x99\xbamSq\xef\x10\xa1e\xa5ns\xae\x02\x17\xbf\xd1}\xf0\xb6nk\xa3~8\xfc\x04X<\xab\x16\xadR5\x9f \xbc\x01\x1cv\x87z\x1e\xe8)\x98\xd3\x96\x96\xcd9R\x87,\x9f\x93\xba\xe9\xcabR\xccP\xdbCRR\xd7%\xd7eK\x16\xb3\x99Ub\xe9v\xd8\x99\xd3\x1dn\x1c\xa19B\xf7\xc4\xa7Je\x93\xfa\xaf\xf1\x11\xb0\xfd\xb0R\xf9\xf9\xacR\xd9~N\x1a\xd6\x81\x97\xfao\xc0\xbc\xfdE\xc0x\x8b\x89\x00\x00\x00\x97IDAT(\x15\x9d\x92\x81\x0e\x80 \x08D\xa5\xf9m\xf5Y\xad\xcf\xaa\x9f#nz$\xba\xb9\xca\xad\x85\xc1\xbd\x03S\xd4\x96H\xf2\xa5\xea\xe1\xeb@\x8e\x02\xd0}\x14/\x80\x03\xca\xa75{\xeb0\x80\x01\xa9\xa0\xdcC|\x02:\xf1\xc3U\xc7\\K\x97}\xda9HPcq0pQ\x8aE\xe94y\x05'3\x92M[\x86\xc7\xc1\xa4n\x82\x01\x8ci\xe2\xc5\x7f\x02N`\xda\xdcCK\xaeqbqsD\xbd\x86=\xe0g\xdb\x9dy\xba\xb4Xp\x8bX\xf0\xe7\x8d\x89g\x84pD_\x0cx\x9438x7\xa4yC\r7\x04z\xae\x00\x00\x00\x00IEND\xaeB`\x82"
    return strings.NewReader(img_str)
}


