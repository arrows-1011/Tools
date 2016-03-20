<!DOCTYPE html>
<html lang='ja'>
	<head>
		<meta charset='utf-8'>
		<title>電卓</title>
	</head>
	<body>
		<h1>電卓</h1>
		<?php
			function fact($str, &$idx)
			{
				$ret = 0;
				if ($str[$idx] == '(') {
					++$idx;
					$ret = expr($str, $idx);
					++$idx;
				} else {
					while ('0' <= $str[$idx] && $str[$idx] <= '9') {
						$ret *= 10;
						$ret += $str[$idx] - '0';
						++$idx;
					}
				}
				return $ret;
			}

			function term($str, &$idx)
			{
				$ret = fact($str, $idx);
				while ($str[$idx] == '*' || $str[$idx] == '/') {
					if ($str[$idx] == '*') {
						++$idx;
						$ret *= fact($str, $idx);
					} else {
						++$idx;
						$ret /= fact($str, $idx);
					}
				}
				return $ret;
			}

			function expr($str, &$idx)
			{
				$ret = term($str, $idx);
				while ($str[$idx] == '+' || $str[$idx] == '-') {
					if ($str[$idx] == '+') {
						++$idx;
						$ret += term($str, $idx);
					} else {
						++$idx;
						$ret -= term($str, $idx);
					}
				}
				return $ret;
			}

			function is_invalid_value($str)
			{
				if (strlen($str) > 15) {
					return true;
				}

				for ($i = 0; $i < strlen($str); $i++) {
					if ($str[$i] != '+' &&
					    $str[$i] != '-' &&
						$str[$i] != '*' &&
						$str[$i] != '/' &&
                        $str[$i] != '(' &&
                        $str[$i] != ')' &&
						!('0' <= $str[$i] && $str[$i] <= '9')) {
						return true;
					}
				}
				return false;
			}

			$str = $_POST['str'];
			if (is_invalid_value($str)) {
				echo htmlspecialchars("Invalid value");
			} else {
				$idx = 0;
				$result = expr($str, $idx);
				echo htmlspecialchars($str)." = ".htmlspecialchars($result);
		    }
		 ?>
		 <br />
		 <a href="index.html">もう一度計算する</a>
	</body>
</html>