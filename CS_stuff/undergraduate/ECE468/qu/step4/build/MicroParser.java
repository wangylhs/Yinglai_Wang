// Generated from Micro.g4 by ANTLR 4.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class MicroParser extends Parser {
	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__32=1, T__31=2, T__30=3, T__29=4, T__28=5, T__27=6, T__26=7, T__25=8, 
		T__24=9, T__23=10, T__22=11, T__21=12, T__20=13, T__19=14, T__18=15, T__17=16, 
		T__16=17, T__15=18, T__14=19, T__13=20, T__12=21, T__11=22, T__10=23, 
		T__9=24, T__8=25, T__7=26, T__6=27, T__5=28, T__4=29, T__3=30, T__2=31, 
		T__1=32, T__0=33, IDENTIFIER=34, INTLITERAL=35, FLOATLITERAL=36, STRINGLITERAL=37, 
		COMMENT=38, WS=39, Operators=40, Keywords=41;
	public static final String[] tokenNames = {
		"<INVALID>", "','", "'DO'", "'*'", "'-'", "'PROGRAM'", "'('", "'READ'", 
		"'<'", "'END'", "'!='", "'<='", "'ENDIF'", "'VOID'", "'STRING'", "'IF'", 
		"'TRUE'", "'FALSE'", "'WRITE'", "')'", "'+'", "'WHILE'", "'ELSIF'", "'='", 
		"';'", "'FUNCTION'", "'>'", "'FLOAT'", "':='", "'RETURN'", "'/'", "'BEGIN'", 
		"'>='", "'INT'", "IDENTIFIER", "INTLITERAL", "FLOATLITERAL", "STRINGLITERAL", 
		"COMMENT", "WS", "Operators", "Keywords"
	};
	public static final int
		RULE_program = 0, RULE_id = 1, RULE_pgm_body = 2, RULE_decl = 3, RULE_string_decl = 4, 
		RULE_str = 5, RULE_var_decl = 6, RULE_var_type = 7, RULE_any_type = 8, 
		RULE_id_list = 9, RULE_param_decl_list = 10, RULE_param_decl = 11, RULE_func_declarations = 12, 
		RULE_func_decl = 13, RULE_func_body = 14, RULE_stmt_list = 15, RULE_stmt = 16, 
		RULE_base_stmt = 17, RULE_assign_stmt = 18, RULE_assign_expr = 19, RULE_read_stmt = 20, 
		RULE_write_stmt = 21, RULE_return_stmt = 22, RULE_expr = 23, RULE_factor = 24, 
		RULE_postfix_expr = 25, RULE_call_expr = 26, RULE_expr_list = 27, RULE_primary = 28, 
		RULE_addop = 29, RULE_mulop = 30, RULE_if_stmt = 31, RULE_else_part = 32, 
		RULE_cond = 33, RULE_compop = 34, RULE_do_while_stmt = 35;
	public static final String[] ruleNames = {
		"program", "id", "pgm_body", "decl", "string_decl", "str", "var_decl", 
		"var_type", "any_type", "id_list", "param_decl_list", "param_decl", "func_declarations", 
		"func_decl", "func_body", "stmt_list", "stmt", "base_stmt", "assign_stmt", 
		"assign_expr", "read_stmt", "write_stmt", "return_stmt", "expr", "factor", 
		"postfix_expr", "call_expr", "expr_list", "primary", "addop", "mulop", 
		"if_stmt", "else_part", "cond", "compop", "do_while_stmt"
	};

	@Override
	public String getGrammarFileName() { return "Micro.g4"; }

	@Override
	public String[] getTokenNames() { return tokenNames; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public MicroParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ProgramContext extends ParserRuleContext {
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public Pgm_bodyContext pgm_body() {
			return getRuleContext(Pgm_bodyContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterProgram(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitProgram(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(72); match(5);
			setState(73); id();
			setState(74); match(31);
			setState(75); pgm_body();
			setState(76); match(9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IdContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(MicroParser.IDENTIFIER, 0); }
		public IdContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_id; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterId(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitId(this);
		}
	}

	public final IdContext id() throws RecognitionException {
		IdContext _localctx = new IdContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_id);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(78); match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Pgm_bodyContext extends ParserRuleContext {
		public Func_declarationsContext func_declarations() {
			return getRuleContext(Func_declarationsContext.class,0);
		}
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public Pgm_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pgm_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterPgm_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitPgm_body(this);
		}
	}

	public final Pgm_bodyContext pgm_body() throws RecognitionException {
		Pgm_bodyContext _localctx = new Pgm_bodyContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_pgm_body);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(80); decl();
			setState(81); func_declarations();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DeclContext extends ParserRuleContext {
		public Var_declContext var_decl(int i) {
			return getRuleContext(Var_declContext.class,i);
		}
		public List<String_declContext> string_decl() {
			return getRuleContexts(String_declContext.class);
		}
		public List<Var_declContext> var_decl() {
			return getRuleContexts(Var_declContext.class);
		}
		public String_declContext string_decl(int i) {
			return getRuleContext(String_declContext.class,i);
		}
		public DeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterDecl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitDecl(this);
		}
	}

	public final DeclContext decl() throws RecognitionException {
		DeclContext _localctx = new DeclContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(87);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << 14) | (1L << 27) | (1L << 33))) != 0)) {
				{
				setState(85);
				switch (_input.LA(1)) {
				case 14:
					{
					setState(83); string_decl();
					}
					break;
				case 27:
				case 33:
					{
					setState(84); var_decl();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(89);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class String_declContext extends ParserRuleContext {
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public StrContext str() {
			return getRuleContext(StrContext.class,0);
		}
		public String_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_string_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterString_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitString_decl(this);
		}
	}

	public final String_declContext string_decl() throws RecognitionException {
		String_declContext _localctx = new String_declContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_string_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(90); match(14);
			setState(91); id();
			setState(92); match(28);
			setState(93); str();
			setState(94); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StrContext extends ParserRuleContext {
		public TerminalNode STRINGLITERAL() { return getToken(MicroParser.STRINGLITERAL, 0); }
		public StrContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_str; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterStr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitStr(this);
		}
	}

	public final StrContext str() throws RecognitionException {
		StrContext _localctx = new StrContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_str);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(96); match(STRINGLITERAL);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Var_declContext extends ParserRuleContext {
		public Id_listContext id_list() {
			return getRuleContext(Id_listContext.class,0);
		}
		public Var_typeContext var_type() {
			return getRuleContext(Var_typeContext.class,0);
		}
		public Var_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterVar_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitVar_decl(this);
		}
	}

	public final Var_declContext var_decl() throws RecognitionException {
		Var_declContext _localctx = new Var_declContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_var_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(98); var_type();
			setState(99); id_list();
			setState(100); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Var_typeContext extends ParserRuleContext {
		public Var_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_var_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterVar_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitVar_type(this);
		}
	}

	public final Var_typeContext var_type() throws RecognitionException {
		Var_typeContext _localctx = new Var_typeContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_var_type);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(102);
			_la = _input.LA(1);
			if ( !(_la==27 || _la==33) ) {
			_errHandler.recoverInline(this);
			}
			consume();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Any_typeContext extends ParserRuleContext {
		public Var_typeContext var_type() {
			return getRuleContext(Var_typeContext.class,0);
		}
		public Any_typeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_any_type; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterAny_type(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitAny_type(this);
		}
	}

	public final Any_typeContext any_type() throws RecognitionException {
		Any_typeContext _localctx = new Any_typeContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_any_type);
		try {
			setState(106);
			switch (_input.LA(1)) {
			case 27:
			case 33:
				enterOuterAlt(_localctx, 1);
				{
				setState(104); var_type();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 2);
				{
				setState(105); match(13);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Id_listContext extends ParserRuleContext {
		public List<IdContext> id() {
			return getRuleContexts(IdContext.class);
		}
		public IdContext id(int i) {
			return getRuleContext(IdContext.class,i);
		}
		public Id_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_id_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterId_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitId_list(this);
		}
	}

	public final Id_listContext id_list() throws RecognitionException {
		Id_listContext _localctx = new Id_listContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_id_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(108); id();
			setState(113);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==1) {
				{
				{
				setState(109); match(1);
				setState(110); id();
				}
				}
				setState(115);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Param_decl_listContext extends ParserRuleContext {
		public Param_declContext param_decl(int i) {
			return getRuleContext(Param_declContext.class,i);
		}
		public List<Param_declContext> param_decl() {
			return getRuleContexts(Param_declContext.class);
		}
		public Param_decl_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param_decl_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterParam_decl_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitParam_decl_list(this);
		}
	}

	public final Param_decl_listContext param_decl_list() throws RecognitionException {
		Param_decl_listContext _localctx = new Param_decl_listContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_param_decl_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(116); param_decl();
			setState(121);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==1) {
				{
				{
				setState(117); match(1);
				setState(118); param_decl();
				}
				}
				setState(123);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Param_declContext extends ParserRuleContext {
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public Var_typeContext var_type() {
			return getRuleContext(Var_typeContext.class,0);
		}
		public Param_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_param_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterParam_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitParam_decl(this);
		}
	}

	public final Param_declContext param_decl() throws RecognitionException {
		Param_declContext _localctx = new Param_declContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_param_decl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(124); var_type();
			setState(125); id();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Func_declarationsContext extends ParserRuleContext {
		public List<Func_declContext> func_decl() {
			return getRuleContexts(Func_declContext.class);
		}
		public Func_declContext func_decl(int i) {
			return getRuleContext(Func_declContext.class,i);
		}
		public Func_declarationsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_declarations; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterFunc_declarations(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitFunc_declarations(this);
		}
	}

	public final Func_declarationsContext func_declarations() throws RecognitionException {
		Func_declarationsContext _localctx = new Func_declarationsContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_func_declarations);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(130);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==25) {
				{
				{
				setState(127); func_decl();
				}
				}
				setState(132);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Func_declContext extends ParserRuleContext {
		public Func_bodyContext func_body() {
			return getRuleContext(Func_bodyContext.class,0);
		}
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public Param_decl_listContext param_decl_list() {
			return getRuleContext(Param_decl_listContext.class,0);
		}
		public Any_typeContext any_type() {
			return getRuleContext(Any_typeContext.class,0);
		}
		public Func_declContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_decl; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterFunc_decl(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitFunc_decl(this);
		}
	}

	public final Func_declContext func_decl() throws RecognitionException {
		Func_declContext _localctx = new Func_declContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_func_decl);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(133); match(25);
			setState(134); any_type();
			setState(135); id();
			setState(136); match(6);
			setState(138);
			_la = _input.LA(1);
			if (_la==27 || _la==33) {
				{
				setState(137); param_decl_list();
				}
			}

			setState(140); match(19);
			setState(141); match(31);
			setState(142); func_body();
			setState(143); match(9);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Func_bodyContext extends ParserRuleContext {
		public Stmt_listContext stmt_list() {
			return getRuleContext(Stmt_listContext.class,0);
		}
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public Func_bodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_func_body; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterFunc_body(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitFunc_body(this);
		}
	}

	public final Func_bodyContext func_body() throws RecognitionException {
		Func_bodyContext _localctx = new Func_bodyContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_func_body);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145); decl();
			setState(146); stmt_list();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Stmt_listContext extends ParserRuleContext {
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public Stmt_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterStmt_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitStmt_list(this);
		}
	}

	public final Stmt_listContext stmt_list() throws RecognitionException {
		Stmt_listContext _localctx = new Stmt_listContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_stmt_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(151);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << 2) | (1L << 7) | (1L << 15) | (1L << 18) | (1L << 29) | (1L << IDENTIFIER))) != 0)) {
				{
				{
				setState(148); stmt();
				}
				}
				setState(153);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StmtContext extends ParserRuleContext {
		public Base_stmtContext base_stmt() {
			return getRuleContext(Base_stmtContext.class,0);
		}
		public If_stmtContext if_stmt() {
			return getRuleContext(If_stmtContext.class,0);
		}
		public Do_while_stmtContext do_while_stmt() {
			return getRuleContext(Do_while_stmtContext.class,0);
		}
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterStmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitStmt(this);
		}
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_stmt);
		try {
			setState(157);
			switch (_input.LA(1)) {
			case 7:
			case 18:
			case 29:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(154); base_stmt();
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 2);
				{
				setState(155); if_stmt();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 3);
				{
				setState(156); do_while_stmt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Base_stmtContext extends ParserRuleContext {
		public Write_stmtContext write_stmt() {
			return getRuleContext(Write_stmtContext.class,0);
		}
		public Read_stmtContext read_stmt() {
			return getRuleContext(Read_stmtContext.class,0);
		}
		public Return_stmtContext return_stmt() {
			return getRuleContext(Return_stmtContext.class,0);
		}
		public Assign_stmtContext assign_stmt() {
			return getRuleContext(Assign_stmtContext.class,0);
		}
		public Base_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_base_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterBase_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitBase_stmt(this);
		}
	}

	public final Base_stmtContext base_stmt() throws RecognitionException {
		Base_stmtContext _localctx = new Base_stmtContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_base_stmt);
		try {
			setState(163);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(159); assign_stmt();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 2);
				{
				setState(160); read_stmt();
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 3);
				{
				setState(161); write_stmt();
				}
				break;
			case 29:
				enterOuterAlt(_localctx, 4);
				{
				setState(162); return_stmt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Assign_stmtContext extends ParserRuleContext {
		public Assign_exprContext assign_expr() {
			return getRuleContext(Assign_exprContext.class,0);
		}
		public Assign_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assign_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterAssign_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitAssign_stmt(this);
		}
	}

	public final Assign_stmtContext assign_stmt() throws RecognitionException {
		Assign_stmtContext _localctx = new Assign_stmtContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_assign_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(165); assign_expr();
			setState(166); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Assign_exprContext extends ParserRuleContext {
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Assign_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assign_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterAssign_expr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitAssign_expr(this);
		}
	}

	public final Assign_exprContext assign_expr() throws RecognitionException {
		Assign_exprContext _localctx = new Assign_exprContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_assign_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(168); id();
			setState(169); match(28);
			setState(170); expr();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Read_stmtContext extends ParserRuleContext {
		public Id_listContext id_list() {
			return getRuleContext(Id_listContext.class,0);
		}
		public Read_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_read_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterRead_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitRead_stmt(this);
		}
	}

	public final Read_stmtContext read_stmt() throws RecognitionException {
		Read_stmtContext _localctx = new Read_stmtContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_read_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(172); match(7);
			setState(173); match(6);
			setState(174); id_list();
			setState(175); match(19);
			setState(176); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Write_stmtContext extends ParserRuleContext {
		public Id_listContext id_list() {
			return getRuleContext(Id_listContext.class,0);
		}
		public Write_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_write_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterWrite_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitWrite_stmt(this);
		}
	}

	public final Write_stmtContext write_stmt() throws RecognitionException {
		Write_stmtContext _localctx = new Write_stmtContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_write_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(178); match(18);
			setState(179); match(6);
			setState(180); id_list();
			setState(181); match(19);
			setState(182); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Return_stmtContext extends ParserRuleContext {
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Return_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_return_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterReturn_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitReturn_stmt(this);
		}
	}

	public final Return_stmtContext return_stmt() throws RecognitionException {
		Return_stmtContext _localctx = new Return_stmtContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_return_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(184); match(29);
			setState(185); expr();
			setState(186); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExprContext extends ParserRuleContext {
		public FactorContext factor(int i) {
			return getRuleContext(FactorContext.class,i);
		}
		public AddopContext addop(int i) {
			return getRuleContext(AddopContext.class,i);
		}
		public List<FactorContext> factor() {
			return getRuleContexts(FactorContext.class);
		}
		public List<AddopContext> addop() {
			return getRuleContexts(AddopContext.class);
		}
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterExpr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitExpr(this);
		}
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_expr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(188); factor();
			setState(194);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==4 || _la==20) {
				{
				{
				setState(189); addop();
				setState(190); factor();
				}
				}
				setState(196);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FactorContext extends ParserRuleContext {
		public List<MulopContext> mulop() {
			return getRuleContexts(MulopContext.class);
		}
		public List<Postfix_exprContext> postfix_expr() {
			return getRuleContexts(Postfix_exprContext.class);
		}
		public Postfix_exprContext postfix_expr(int i) {
			return getRuleContext(Postfix_exprContext.class,i);
		}
		public MulopContext mulop(int i) {
			return getRuleContext(MulopContext.class,i);
		}
		public FactorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_factor; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterFactor(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitFactor(this);
		}
	}

	public final FactorContext factor() throws RecognitionException {
		FactorContext _localctx = new FactorContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_factor);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(197); postfix_expr();
			setState(203);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==3 || _la==30) {
				{
				{
				setState(198); mulop();
				setState(199); postfix_expr();
				}
				}
				setState(205);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Postfix_exprContext extends ParserRuleContext {
		public PrimaryContext primary() {
			return getRuleContext(PrimaryContext.class,0);
		}
		public Call_exprContext call_expr() {
			return getRuleContext(Call_exprContext.class,0);
		}
		public Postfix_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_postfix_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterPostfix_expr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitPostfix_expr(this);
		}
	}

	public final Postfix_exprContext postfix_expr() throws RecognitionException {
		Postfix_exprContext _localctx = new Postfix_exprContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_postfix_expr);
		try {
			setState(208);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(206); primary();
				}
				break;

			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(207); call_expr();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Call_exprContext extends ParserRuleContext {
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public Expr_listContext expr_list() {
			return getRuleContext(Expr_listContext.class,0);
		}
		public Call_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_call_expr; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterCall_expr(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitCall_expr(this);
		}
	}

	public final Call_exprContext call_expr() throws RecognitionException {
		Call_exprContext _localctx = new Call_exprContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_call_expr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(210); id();
			setState(211); match(6);
			setState(213);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << 6) | (1L << IDENTIFIER) | (1L << INTLITERAL) | (1L << FLOATLITERAL))) != 0)) {
				{
				setState(212); expr_list();
				}
			}

			setState(215); match(19);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Expr_listContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public Expr_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_list; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterExpr_list(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitExpr_list(this);
		}
	}

	public final Expr_listContext expr_list() throws RecognitionException {
		Expr_listContext _localctx = new Expr_listContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_expr_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(217); expr();
			setState(222);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==1) {
				{
				{
				setState(218); match(1);
				setState(219); expr();
				}
				}
				setState(224);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PrimaryContext extends ParserRuleContext {
		public TerminalNode FLOATLITERAL() { return getToken(MicroParser.FLOATLITERAL, 0); }
		public IdContext id() {
			return getRuleContext(IdContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode INTLITERAL() { return getToken(MicroParser.INTLITERAL, 0); }
		public PrimaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primary; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterPrimary(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitPrimary(this);
		}
	}

	public final PrimaryContext primary() throws RecognitionException {
		PrimaryContext _localctx = new PrimaryContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_primary);
		try {
			setState(232);
			switch (_input.LA(1)) {
			case 6:
				enterOuterAlt(_localctx, 1);
				{
				setState(225); match(6);
				setState(226); expr();
				setState(227); match(19);
				}
				break;
			case IDENTIFIER:
				enterOuterAlt(_localctx, 2);
				{
				setState(229); id();
				}
				break;
			case INTLITERAL:
				enterOuterAlt(_localctx, 3);
				{
				setState(230); match(INTLITERAL);
				}
				break;
			case FLOATLITERAL:
				enterOuterAlt(_localctx, 4);
				{
				setState(231); match(FLOATLITERAL);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AddopContext extends ParserRuleContext {
		public AddopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addop; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterAddop(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitAddop(this);
		}
	}

	public final AddopContext addop() throws RecognitionException {
		AddopContext _localctx = new AddopContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_addop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(234);
			_la = _input.LA(1);
			if ( !(_la==4 || _la==20) ) {
			_errHandler.recoverInline(this);
			}
			consume();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MulopContext extends ParserRuleContext {
		public MulopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_mulop; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterMulop(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitMulop(this);
		}
	}

	public final MulopContext mulop() throws RecognitionException {
		MulopContext _localctx = new MulopContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_mulop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(236);
			_la = _input.LA(1);
			if ( !(_la==3 || _la==30) ) {
			_errHandler.recoverInline(this);
			}
			consume();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class If_stmtContext extends ParserRuleContext {
		public Stmt_listContext stmt_list() {
			return getRuleContext(Stmt_listContext.class,0);
		}
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public CondContext cond() {
			return getRuleContext(CondContext.class,0);
		}
		public Else_partContext else_part() {
			return getRuleContext(Else_partContext.class,0);
		}
		public If_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_if_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterIf_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitIf_stmt(this);
		}
	}

	public final If_stmtContext if_stmt() throws RecognitionException {
		If_stmtContext _localctx = new If_stmtContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_if_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(238); match(15);
			setState(239); match(6);
			setState(240); cond();
			setState(241); match(19);
			setState(242); decl();
			setState(243); stmt_list();
			setState(244); else_part();
			setState(245); match(12);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Else_partContext extends ParserRuleContext {
		public List<Stmt_listContext> stmt_list() {
			return getRuleContexts(Stmt_listContext.class);
		}
		public Else_partContext else_part(int i) {
			return getRuleContext(Else_partContext.class,i);
		}
		public List<DeclContext> decl() {
			return getRuleContexts(DeclContext.class);
		}
		public Stmt_listContext stmt_list(int i) {
			return getRuleContext(Stmt_listContext.class,i);
		}
		public CondContext cond(int i) {
			return getRuleContext(CondContext.class,i);
		}
		public List<CondContext> cond() {
			return getRuleContexts(CondContext.class);
		}
		public DeclContext decl(int i) {
			return getRuleContext(DeclContext.class,i);
		}
		public List<Else_partContext> else_part() {
			return getRuleContexts(Else_partContext.class);
		}
		public Else_partContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_else_part; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterElse_part(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitElse_part(this);
		}
	}

	public final Else_partContext else_part() throws RecognitionException {
		Else_partContext _localctx = new Else_partContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_else_part);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(257);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			while ( _alt!=2 && _alt!=-1 ) {
				if ( _alt==1 ) {
					{
					{
					setState(247); match(22);
					setState(248); match(6);
					setState(249); cond();
					setState(250); match(19);
					setState(251); decl();
					setState(252); stmt_list();
					setState(253); else_part();
					}
					} 
				}
				setState(259);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,16,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CondContext extends ParserRuleContext {
		public CompopContext compop() {
			return getRuleContext(CompopContext.class,0);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public CondContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cond; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterCond(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitCond(this);
		}
	}

	public final CondContext cond() throws RecognitionException {
		CondContext _localctx = new CondContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_cond);
		try {
			setState(266);
			switch (_input.LA(1)) {
			case 6:
			case IDENTIFIER:
			case INTLITERAL:
			case FLOATLITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(260); expr();
				setState(261); compop();
				setState(262); expr();
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 2);
				{
				setState(264); match(16);
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 3);
				{
				setState(265); match(17);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CompopContext extends ParserRuleContext {
		public CompopContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_compop; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterCompop(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitCompop(this);
		}
	}

	public final CompopContext compop() throws RecognitionException {
		CompopContext _localctx = new CompopContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_compop);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(268);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << 8) | (1L << 10) | (1L << 11) | (1L << 23) | (1L << 26) | (1L << 32))) != 0)) ) {
			_errHandler.recoverInline(this);
			}
			consume();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Do_while_stmtContext extends ParserRuleContext {
		public Stmt_listContext stmt_list() {
			return getRuleContext(Stmt_listContext.class,0);
		}
		public DeclContext decl() {
			return getRuleContext(DeclContext.class,0);
		}
		public CondContext cond() {
			return getRuleContext(CondContext.class,0);
		}
		public Do_while_stmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_do_while_stmt; }
		@Override
		public void enterRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).enterDo_while_stmt(this);
		}
		@Override
		public void exitRule(ParseTreeListener listener) {
			if ( listener instanceof MicroListener ) ((MicroListener)listener).exitDo_while_stmt(this);
		}
	}

	public final Do_while_stmtContext do_while_stmt() throws RecognitionException {
		Do_while_stmtContext _localctx = new Do_while_stmtContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_do_while_stmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(270); match(2);
			setState(271); decl();
			setState(272); stmt_list();
			setState(273); match(21);
			setState(274); match(6);
			setState(275); cond();
			setState(276); match(19);
			setState(277); match(24);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\uacf5\uee8c\u4f5d\u8b0d\u4a45\u78bd\u1b2f\u3378\3+\u011a\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\3\2\3\2\3\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4"+
		"\3\4\3\5\3\5\7\5X\n\5\f\5\16\5[\13\5\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3"+
		"\b\3\b\3\b\3\b\3\t\3\t\3\n\3\n\5\nm\n\n\3\13\3\13\3\13\7\13r\n\13\f\13"+
		"\16\13u\13\13\3\f\3\f\3\f\7\fz\n\f\f\f\16\f}\13\f\3\r\3\r\3\r\3\16\7\16"+
		"\u0083\n\16\f\16\16\16\u0086\13\16\3\17\3\17\3\17\3\17\3\17\5\17\u008d"+
		"\n\17\3\17\3\17\3\17\3\17\3\17\3\20\3\20\3\20\3\21\7\21\u0098\n\21\f\21"+
		"\16\21\u009b\13\21\3\22\3\22\3\22\5\22\u00a0\n\22\3\23\3\23\3\23\3\23"+
		"\5\23\u00a6\n\23\3\24\3\24\3\24\3\25\3\25\3\25\3\25\3\26\3\26\3\26\3\26"+
		"\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\3\31\3\31"+
		"\3\31\3\31\7\31\u00c3\n\31\f\31\16\31\u00c6\13\31\3\32\3\32\3\32\3\32"+
		"\7\32\u00cc\n\32\f\32\16\32\u00cf\13\32\3\33\3\33\5\33\u00d3\n\33\3\34"+
		"\3\34\3\34\5\34\u00d8\n\34\3\34\3\34\3\35\3\35\3\35\7\35\u00df\n\35\f"+
		"\35\16\35\u00e2\13\35\3\36\3\36\3\36\3\36\3\36\3\36\3\36\5\36\u00eb\n"+
		"\36\3\37\3\37\3 \3 \3!\3!\3!\3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3\""+
		"\3\"\3\"\7\"\u0102\n\"\f\"\16\"\u0105\13\"\3#\3#\3#\3#\3#\3#\5#\u010d"+
		"\n#\3$\3$\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\2&\2\4\6\b\n\f\16\20\22\24\26"+
		"\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BDFH\2\6\4\2\35\35##\4\2\6\6\26"+
		"\26\4\2\5\5  \7\2\n\n\f\r\31\31\34\34\"\"\u010d\2J\3\2\2\2\4P\3\2\2\2"+
		"\6R\3\2\2\2\bY\3\2\2\2\n\\\3\2\2\2\fb\3\2\2\2\16d\3\2\2\2\20h\3\2\2\2"+
		"\22l\3\2\2\2\24n\3\2\2\2\26v\3\2\2\2\30~\3\2\2\2\32\u0084\3\2\2\2\34\u0087"+
		"\3\2\2\2\36\u0093\3\2\2\2 \u0099\3\2\2\2\"\u009f\3\2\2\2$\u00a5\3\2\2"+
		"\2&\u00a7\3\2\2\2(\u00aa\3\2\2\2*\u00ae\3\2\2\2,\u00b4\3\2\2\2.\u00ba"+
		"\3\2\2\2\60\u00be\3\2\2\2\62\u00c7\3\2\2\2\64\u00d2\3\2\2\2\66\u00d4\3"+
		"\2\2\28\u00db\3\2\2\2:\u00ea\3\2\2\2<\u00ec\3\2\2\2>\u00ee\3\2\2\2@\u00f0"+
		"\3\2\2\2B\u0103\3\2\2\2D\u010c\3\2\2\2F\u010e\3\2\2\2H\u0110\3\2\2\2J"+
		"K\7\7\2\2KL\5\4\3\2LM\7!\2\2MN\5\6\4\2NO\7\13\2\2O\3\3\2\2\2PQ\7$\2\2"+
		"Q\5\3\2\2\2RS\5\b\5\2ST\5\32\16\2T\7\3\2\2\2UX\5\n\6\2VX\5\16\b\2WU\3"+
		"\2\2\2WV\3\2\2\2X[\3\2\2\2YW\3\2\2\2YZ\3\2\2\2Z\t\3\2\2\2[Y\3\2\2\2\\"+
		"]\7\20\2\2]^\5\4\3\2^_\7\36\2\2_`\5\f\7\2`a\7\32\2\2a\13\3\2\2\2bc\7\'"+
		"\2\2c\r\3\2\2\2de\5\20\t\2ef\5\24\13\2fg\7\32\2\2g\17\3\2\2\2hi\t\2\2"+
		"\2i\21\3\2\2\2jm\5\20\t\2km\7\17\2\2lj\3\2\2\2lk\3\2\2\2m\23\3\2\2\2n"+
		"s\5\4\3\2op\7\3\2\2pr\5\4\3\2qo\3\2\2\2ru\3\2\2\2sq\3\2\2\2st\3\2\2\2"+
		"t\25\3\2\2\2us\3\2\2\2v{\5\30\r\2wx\7\3\2\2xz\5\30\r\2yw\3\2\2\2z}\3\2"+
		"\2\2{y\3\2\2\2{|\3\2\2\2|\27\3\2\2\2}{\3\2\2\2~\177\5\20\t\2\177\u0080"+
		"\5\4\3\2\u0080\31\3\2\2\2\u0081\u0083\5\34\17\2\u0082\u0081\3\2\2\2\u0083"+
		"\u0086\3\2\2\2\u0084\u0082\3\2\2\2\u0084\u0085\3\2\2\2\u0085\33\3\2\2"+
		"\2\u0086\u0084\3\2\2\2\u0087\u0088\7\33\2\2\u0088\u0089\5\22\n\2\u0089"+
		"\u008a\5\4\3\2\u008a\u008c\7\b\2\2\u008b\u008d\5\26\f\2\u008c\u008b\3"+
		"\2\2\2\u008c\u008d\3\2\2\2\u008d\u008e\3\2\2\2\u008e\u008f\7\25\2\2\u008f"+
		"\u0090\7!\2\2\u0090\u0091\5\36\20\2\u0091\u0092\7\13\2\2\u0092\35\3\2"+
		"\2\2\u0093\u0094\5\b\5\2\u0094\u0095\5 \21\2\u0095\37\3\2\2\2\u0096\u0098"+
		"\5\"\22\2\u0097\u0096\3\2\2\2\u0098\u009b\3\2\2\2\u0099\u0097\3\2\2\2"+
		"\u0099\u009a\3\2\2\2\u009a!\3\2\2\2\u009b\u0099\3\2\2\2\u009c\u00a0\5"+
		"$\23\2\u009d\u00a0\5@!\2\u009e\u00a0\5H%\2\u009f\u009c\3\2\2\2\u009f\u009d"+
		"\3\2\2\2\u009f\u009e\3\2\2\2\u00a0#\3\2\2\2\u00a1\u00a6\5&\24\2\u00a2"+
		"\u00a6\5*\26\2\u00a3\u00a6\5,\27\2\u00a4\u00a6\5.\30\2\u00a5\u00a1\3\2"+
		"\2\2\u00a5\u00a2\3\2\2\2\u00a5\u00a3\3\2\2\2\u00a5\u00a4\3\2\2\2\u00a6"+
		"%\3\2\2\2\u00a7\u00a8\5(\25\2\u00a8\u00a9\7\32\2\2\u00a9\'\3\2\2\2\u00aa"+
		"\u00ab\5\4\3\2\u00ab\u00ac\7\36\2\2\u00ac\u00ad\5\60\31\2\u00ad)\3\2\2"+
		"\2\u00ae\u00af\7\t\2\2\u00af\u00b0\7\b\2\2\u00b0\u00b1\5\24\13\2\u00b1"+
		"\u00b2\7\25\2\2\u00b2\u00b3\7\32\2\2\u00b3+\3\2\2\2\u00b4\u00b5\7\24\2"+
		"\2\u00b5\u00b6\7\b\2\2\u00b6\u00b7\5\24\13\2\u00b7\u00b8\7\25\2\2\u00b8"+
		"\u00b9\7\32\2\2\u00b9-\3\2\2\2\u00ba\u00bb\7\37\2\2\u00bb\u00bc\5\60\31"+
		"\2\u00bc\u00bd\7\32\2\2\u00bd/\3\2\2\2\u00be\u00c4\5\62\32\2\u00bf\u00c0"+
		"\5<\37\2\u00c0\u00c1\5\62\32\2\u00c1\u00c3\3\2\2\2\u00c2\u00bf\3\2\2\2"+
		"\u00c3\u00c6\3\2\2\2\u00c4\u00c2\3\2\2\2\u00c4\u00c5\3\2\2\2\u00c5\61"+
		"\3\2\2\2\u00c6\u00c4\3\2\2\2\u00c7\u00cd\5\64\33\2\u00c8\u00c9\5> \2\u00c9"+
		"\u00ca\5\64\33\2\u00ca\u00cc\3\2\2\2\u00cb\u00c8\3\2\2\2\u00cc\u00cf\3"+
		"\2\2\2\u00cd\u00cb\3\2\2\2\u00cd\u00ce\3\2\2\2\u00ce\63\3\2\2\2\u00cf"+
		"\u00cd\3\2\2\2\u00d0\u00d3\5:\36\2\u00d1\u00d3\5\66\34\2\u00d2\u00d0\3"+
		"\2\2\2\u00d2\u00d1\3\2\2\2\u00d3\65\3\2\2\2\u00d4\u00d5\5\4\3\2\u00d5"+
		"\u00d7\7\b\2\2\u00d6\u00d8\58\35\2\u00d7\u00d6\3\2\2\2\u00d7\u00d8\3\2"+
		"\2\2\u00d8\u00d9\3\2\2\2\u00d9\u00da\7\25\2\2\u00da\67\3\2\2\2\u00db\u00e0"+
		"\5\60\31\2\u00dc\u00dd\7\3\2\2\u00dd\u00df\5\60\31\2\u00de\u00dc\3\2\2"+
		"\2\u00df\u00e2\3\2\2\2\u00e0\u00de\3\2\2\2\u00e0\u00e1\3\2\2\2\u00e19"+
		"\3\2\2\2\u00e2\u00e0\3\2\2\2\u00e3\u00e4\7\b\2\2\u00e4\u00e5\5\60\31\2"+
		"\u00e5\u00e6\7\25\2\2\u00e6\u00eb\3\2\2\2\u00e7\u00eb\5\4\3\2\u00e8\u00eb"+
		"\7%\2\2\u00e9\u00eb\7&\2\2\u00ea\u00e3\3\2\2\2\u00ea\u00e7\3\2\2\2\u00ea"+
		"\u00e8\3\2\2\2\u00ea\u00e9\3\2\2\2\u00eb;\3\2\2\2\u00ec\u00ed\t\3\2\2"+
		"\u00ed=\3\2\2\2\u00ee\u00ef\t\4\2\2\u00ef?\3\2\2\2\u00f0\u00f1\7\21\2"+
		"\2\u00f1\u00f2\7\b\2\2\u00f2\u00f3\5D#\2\u00f3\u00f4\7\25\2\2\u00f4\u00f5"+
		"\5\b\5\2\u00f5\u00f6\5 \21\2\u00f6\u00f7\5B\"\2\u00f7\u00f8\7\16\2\2\u00f8"+
		"A\3\2\2\2\u00f9\u00fa\7\30\2\2\u00fa\u00fb\7\b\2\2\u00fb\u00fc\5D#\2\u00fc"+
		"\u00fd\7\25\2\2\u00fd\u00fe\5\b\5\2\u00fe\u00ff\5 \21\2\u00ff\u0100\5"+
		"B\"\2\u0100\u0102\3\2\2\2\u0101\u00f9\3\2\2\2\u0102\u0105\3\2\2\2\u0103"+
		"\u0101\3\2\2\2\u0103\u0104\3\2\2\2\u0104C\3\2\2\2\u0105\u0103\3\2\2\2"+
		"\u0106\u0107\5\60\31\2\u0107\u0108\5F$\2\u0108\u0109\5\60\31\2\u0109\u010d"+
		"\3\2\2\2\u010a\u010d\7\22\2\2\u010b\u010d\7\23\2\2\u010c\u0106\3\2\2\2"+
		"\u010c\u010a\3\2\2\2\u010c\u010b\3\2\2\2\u010dE\3\2\2\2\u010e\u010f\t"+
		"\5\2\2\u010fG\3\2\2\2\u0110\u0111\7\4\2\2\u0111\u0112\5\b\5\2\u0112\u0113"+
		"\5 \21\2\u0113\u0114\7\27\2\2\u0114\u0115\7\b\2\2\u0115\u0116\5D#\2\u0116"+
		"\u0117\7\25\2\2\u0117\u0118\7\32\2\2\u0118I\3\2\2\2\24WYls{\u0084\u008c"+
		"\u0099\u009f\u00a5\u00c4\u00cd\u00d2\u00d7\u00e0\u00ea\u0103\u010c";
	public static final ATN _ATN =
		ATNSimulator.deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}