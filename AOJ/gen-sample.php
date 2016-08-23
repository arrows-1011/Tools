<?php
if (!syntax_check($argc, $argv)) {
	return;
}

$url = "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=".$argv[1];
$html = file_get_contents($url);

$cnt = preg_match_all('/<(H|h)[0-9]>Sample Input.*<\/(H|h)[0-9]>(.*)<pre>(.+)<\/pre>/s', $html, $res);
# $cnt = preg_match_all('/<pre>(.+)<\/pre>/s', $html, $res);

$str = explode("\n", $res[0][0]);
$num = 1;
$p = 0;

for ($i = 0; $i < count($str); ) {
	if (preg_match('/.*<pre>.*/', $str[$i])) {
		$file_name = ($p % 2 == 0 ? "in" : "out").$num;
		$data = "";
		if ($p % 2 == 1) {
			$num++;
		}
		$i++;
		while (!preg_match('/.*<\/pre>.*/', $str[$i])) {
			$data .= $str[$i];
			$data .= "\n";
			$i++;
		}
		file_put_contents($file_name, $data);
		$p++;
	} else {
		$i++;
	}
}

function syntax_check($argc, $argv) {
	if ($argc != 2) {
		echo "<program> <problem id>\n";
		return false;
	}

	if (!preg_match('#\d{4}#', $argv[1])) {
		echo "problem id is invalid.\n";
		return false;
	}
	return true;
}
 ?>