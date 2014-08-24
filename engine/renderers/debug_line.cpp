/*
Copyright (c) 2013 Daniele Bartolini, Michele Rossi
Copyright (c) 2012 Daniele Bartolini, Simone Boscaratto

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#include "debug_line.h"
#include "math_utils.h"
#include "color4.h"
#include "vector3.h"
#include "config.h"
#include <string.h>
#include <bgfx.h>

namespace crown
{

namespace debug_line
{
#if CROWN_PLATFORM_LINUX || CROWN_PLATFORM_ANDROID
	static const uint8_t vs_h[335] =
	{
		0x56, 0x53, 0x48, 0x03, 0x1c, 0xf0, 0xa8, 0xc9, 0x01, 0x00, 0x0f, 0x75, 0x5f, 0x6d, 0x6f, 0x64, // VSH........u_mod
		0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x09, 0x01, 0x00, 0x00, 0x01, 0x00, // elViewProj......
		0x2a, 0x01, 0x00, 0x00, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x6d, 0x65, // *...attribute me
		0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x61, 0x5f, 0x63, 0x6f, 0x6c, // diump vec4 a_col
		0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x61, 0x74, 0x74, 0x72, 0x69, 0x62, 0x75, 0x74, 0x65, 0x20, 0x6d, // or0;.attribute m
		0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x33, 0x20, 0x61, 0x5f, 0x70, 0x6f, // ediump vec3 a_po
		0x73, 0x69, 0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x76, 0x61, 0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, // sition;.varying 
		0x6d, 0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, // mediump vec4 v_c
		0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x75, 0x6e, 0x69, 0x66, 0x6f, 0x72, 0x6d, 0x20, 0x6d, // olor0;.uniform m
		0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x6d, 0x61, 0x74, 0x34, 0x20, 0x75, 0x5f, 0x6d, 0x6f, // ediump mat4 u_mo
		0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x3b, 0x0a, 0x76, 0x6f, 0x69, // delViewProj;.voi
		0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x6d, 0x65, // d main ().{.  me
		0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, 0x63, 0x34, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // diump vec4 tmpva
		0x72, 0x5f, 0x31, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, 0x31, 0x2e, // r_1;.  tmpvar_1.
		0x77, 0x20, 0x3d, 0x20, 0x31, 0x2e, 0x30, 0x3b, 0x0a, 0x20, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, // w = 1.0;.  tmpva
		0x72, 0x5f, 0x31, 0x2e, 0x78, 0x79, 0x7a, 0x20, 0x3d, 0x20, 0x61, 0x5f, 0x70, 0x6f, 0x73, 0x69, // r_1.xyz = a_posi
		0x74, 0x69, 0x6f, 0x6e, 0x3b, 0x0a, 0x20, 0x20, 0x67, 0x6c, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74, // tion;.  gl_Posit
		0x69, 0x6f, 0x6e, 0x20, 0x3d, 0x20, 0x28, 0x75, 0x5f, 0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, // ion = (u_modelVi
		0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x20, 0x2a, 0x20, 0x74, 0x6d, 0x70, 0x76, 0x61, 0x72, 0x5f, // ewProj * tmpvar_
		0x31, 0x29, 0x3b, 0x0a, 0x20, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x20, 0x3d, // 1);.  v_color0 =
		0x20, 0x61, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,       //  a_color0;.}...
	};

	static const uint8_t fs_h[91] =
	{
		0x46, 0x53, 0x48, 0x03, 0x1c, 0xf0, 0xa8, 0xc9, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x76, 0x61, // FSH.......L...va
		0x72, 0x79, 0x69, 0x6e, 0x67, 0x20, 0x6d, 0x65, 0x64, 0x69, 0x75, 0x6d, 0x70, 0x20, 0x76, 0x65, // rying mediump ve
		0x63, 0x34, 0x20, 0x76, 0x5f, 0x63, 0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x76, 0x6f, 0x69, // c4 v_color0;.voi
		0x64, 0x20, 0x6d, 0x61, 0x69, 0x6e, 0x20, 0x28, 0x29, 0x0a, 0x7b, 0x0a, 0x20, 0x20, 0x67, 0x6c, // d main ().{.  gl
		0x5f, 0x46, 0x72, 0x61, 0x67, 0x43, 0x6f, 0x6c, 0x6f, 0x72, 0x20, 0x3d, 0x20, 0x76, 0x5f, 0x63, // _FragColor = v_c
		0x6f, 0x6c, 0x6f, 0x72, 0x30, 0x3b, 0x0a, 0x7d, 0x0a, 0x0a, 0x00,                               // olor0;.}...
	};
#elif CROWN_PLATFORM_WINDOWS
	static const uint8_t vs_h[419] =
	{
		0x56, 0x53, 0x48, 0x02, 0x1c, 0xf0, 0xa8, 0xc9, 0x01, 0x00, 0x0f, 0x75, 0x5f, 0x6d, 0x6f, 0x64, // VSH........u_mod
		0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x09, 0x01, 0x00, 0x00, 0x04, 0x00, // elViewProj......
		0x80, 0x01, 0x00, 0x03, 0xfe, 0xff, 0xfe, 0xff, 0x23, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, // ........#.CTAB..
		0x00, 0x00, 0x57, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0xff, 0x01, 0x00, 0x00, 0x00, 0x1c, 0x00, // ..W.............
		0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x02, 0x00, // ......P...0.....
		0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x75, 0x5f, // ......@.......u_
		0x6d, 0x6f, 0x64, 0x65, 0x6c, 0x56, 0x69, 0x65, 0x77, 0x50, 0x72, 0x6f, 0x6a, 0x00, 0x03, 0x00, // modelViewProj...
		0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x73, // ..............vs
		0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, // _3_0.Microsoft (
		0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, 0x61, 0x64, 0x65, 0x72, 0x20, 0x43, // R) HLSL Shader C
		0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x39, 0x2e, 0x32, 0x39, 0x2e, 0x39, 0x35, 0x32, // ompiler 9.29.952
		0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x51, 0x00, 0x00, 0x05, 0x04, 0x00, 0x0f, 0xa0, 0x00, 0x00, // .3111.Q.........
		0x80, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, // .?..............
		0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, // ................
		0x00, 0x80, 0x01, 0x00, 0x0f, 0x90, 0x1f, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, // ................
		0x0f, 0xe0, 0x1f, 0x00, 0x00, 0x02, 0x0a, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0f, 0xe0, 0x05, 0x00, // ................
		0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x00, 0x90, 0x05, 0x00, // ................
		0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, 0x01, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0x55, 0x90, 0x02, 0x00, // ............U...
		0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x05, 0x00, // ................
		0x00, 0x03, 0x01, 0x00, 0x0f, 0x80, 0x02, 0x00, 0xe4, 0xa0, 0x01, 0x00, 0xaa, 0x90, 0x02, 0x00, // ................
		0x00, 0x03, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x01, 0x00, // ................
		0x00, 0x02, 0x01, 0x00, 0x0f, 0x80, 0x03, 0x00, 0xe4, 0xa0, 0x05, 0x00, 0x00, 0x03, 0x01, 0x00, // ................
		0x0f, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x04, 0x00, 0x00, 0xa0, 0x02, 0x00, 0x00, 0x03, 0x00, 0x00, // ................
		0x0f, 0x80, 0x00, 0x00, 0xe4, 0x80, 0x01, 0x00, 0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, // ................
		0x0f, 0x80, 0x00, 0x00, 0xe4, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, // ................
		0xe4, 0x80, 0x01, 0x00, 0x00, 0x02, 0x01, 0x00, 0x0f, 0xe0, 0x01, 0x00, 0xe4, 0x80, 0xff, 0xff, // ................
		0x00, 0x00, 0x00,                                                                               // ...
	};

	static const uint8_t fs_h[137] =
	{
		0x46, 0x53, 0x48, 0x02, 0x1c, 0xf0, 0xa8, 0xc9, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x03, 0xff, 0xff, // FSH.......|.....
		0xfe, 0xff, 0x16, 0x00, 0x43, 0x54, 0x41, 0x42, 0x1c, 0x00, 0x00, 0x00, 0x23, 0x00, 0x00, 0x00, // ....CTAB....#...
		0x00, 0x03, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, // ................
		0x1c, 0x00, 0x00, 0x00, 0x70, 0x73, 0x5f, 0x33, 0x5f, 0x30, 0x00, 0x4d, 0x69, 0x63, 0x72, 0x6f, // ....ps_3_0.Micro
		0x73, 0x6f, 0x66, 0x74, 0x20, 0x28, 0x52, 0x29, 0x20, 0x48, 0x4c, 0x53, 0x4c, 0x20, 0x53, 0x68, // soft (R) HLSL Sh
		0x61, 0x64, 0x65, 0x72, 0x20, 0x43, 0x6f, 0x6d, 0x70, 0x69, 0x6c, 0x65, 0x72, 0x20, 0x39, 0x2e, // ader Compiler 9.
		0x32, 0x39, 0x2e, 0x39, 0x35, 0x32, 0x2e, 0x33, 0x31, 0x31, 0x31, 0x00, 0x1f, 0x00, 0x00, 0x02, // 29.952.3111.....
		0x0a, 0x00, 0x00, 0x80, 0x00, 0x00, 0x0f, 0x90, 0x01, 0x00, 0x00, 0x02, 0x00, 0x08, 0x0f, 0x80, // ................
		0x00, 0x00, 0xe4, 0x90, 0xff, 0xff, 0x00, 0x00, 0x00,                                           // .........
	};
#endif

	static bgfx::VertexDecl s_decl;
	static bgfx::ProgramHandle s_prog;

	void init()
	{
		s_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.end();

		bgfx::ShaderHandle vs = bgfx::createShader(
			bgfx::makeRef(vs_h, sizeof(vs_h)));
		bgfx::ShaderHandle fs = bgfx::createShader(
		 	bgfx::makeRef(fs_h, sizeof(fs_h)));

		s_prog = bgfx::createProgram(vs, fs, true);
	}

	void shutdown()
	{
		bgfx::destroyProgram(s_prog);
	}

} // namespace debug_line

//-----------------------------------------------------------------------------
DebugLine::DebugLine(bool depth_test)
	: m_depth_test(depth_test)
	, m_num_lines(0)
{
}

//-----------------------------------------------------------------------------
void DebugLine::add_line(const Color4& color, const Vector3& start, const Vector3& end)
{
	if (m_num_lines >= CE_MAX_DEBUG_LINES)
		 return;

	m_lines[m_num_lines].p0[0] = start.x;
	m_lines[m_num_lines].p0[1] = start.y;
	m_lines[m_num_lines].p0[2] = start.z;
	m_lines[m_num_lines].c0    = color4::to_abgr(color);

	m_lines[m_num_lines].p1[0] = end.x;
	m_lines[m_num_lines].p1[1] = end.y;
	m_lines[m_num_lines].p1[2] = end.z;
	m_lines[m_num_lines].c1    = color4::to_abgr(color);

	m_num_lines++;
}

//-----------------------------------------------------------------------------
void DebugLine::add_sphere(const Color4& color, const Vector3& center, const float radius)
{
	const uint32_t deg_step = 15;

	for (uint32_t deg = 0; deg < 360; deg += deg_step)
	{
		const float rad0 = math::deg_to_rad((float) deg);
		const float rad1 = math::deg_to_rad((float) deg + deg_step);

		// XZ plane
		const Vector3 start0(math::cos(rad0) * radius, 0, -math::sin(rad0) * radius);
		const Vector3 end0  (math::cos(rad1) * radius, 0, -math::sin(rad1) * radius);
		add_line(color, center + start0, center + end0);

		// XY plane
		const Vector3 start1(math::cos(rad0) * radius, math::sin(rad0) * radius, 0);
		const Vector3 end1  (math::cos(rad1) * radius, math::sin(rad1) * radius, 0);
		add_line(color, center + start1, center + end1);

		// YZ plane
		const Vector3 start2(0, math::sin(rad0) * radius, -math::cos(rad0) * radius);
		const Vector3 end2  (0, math::sin(rad1) * radius, -math::cos(rad1) * radius);
		add_line(color, center + start2, center + end2);
	}
}

//-----------------------------------------------------------------------------
void DebugLine::clear()
{
	m_num_lines = 0;
}

//-----------------------------------------------------------------------------
void DebugLine::commit()
{
	if (!m_num_lines)
		return;

	bgfx::TransientVertexBuffer tvb;
	bgfx::allocTransientVertexBuffer(&tvb, CE_MAX_DEBUG_LINES * 2, debug_line::s_decl);

	memcpy(tvb.data, m_lines, sizeof(Line) * m_num_lines);

	bgfx::setState(BGFX_STATE_PT_LINES
		| BGFX_STATE_RGB_WRITE
		| BGFX_STATE_DEPTH_WRITE
		| (m_depth_test ? BGFX_STATE_DEPTH_TEST_LESS
			: BGFX_STATE_DEPTH_TEST_ALWAYS)
		| BGFX_STATE_CULL_CW);

	bgfx::setProgram(debug_line::s_prog);
	bgfx::setVertexBuffer(&tvb, 0, m_num_lines * 2);
	bgfx::submit(0);
}

} // namespace crown
