<?php

/**
 * 检查用户的角色是否是允许登陆的
 */
function _services_login_role_user_login($username, $password) {
	$account = user_load_by_name($username);

	if ($account) {
		$allowed_roles = variable_get('services_login_allowed_roles', array());

		$allowed = FALSE;
		foreach ($account->roles as $rid => $role) {
			if (isset($allowed_roles[$rid])) {
				$allowed = TRUE;
				break;
			}
		}
		
		if (!$allowed) {
			return services_error(t('你的用户角色被禁止登陆。'), 403);
		}
		
		module_load_include('inc', 'services', 'resources/user_resource');
	  return _user_resource_login($username, $password);
	}
	else {
		return services_error(t('用户名或密码错误。'), 401);
	}
}